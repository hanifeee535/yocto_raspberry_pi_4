#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QObject>

class SystemMonitor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double cpuUsage READ cpuUsage NOTIFY cpuUsageChanged)
    Q_PROPERTY(double ramUsage READ ramUsage NOTIFY ramUsageChanged)
    Q_PROPERTY(int temperature READ temperature NOTIFY temperatureChanged)

public:
    explicit SystemMonitor(QObject *parent = nullptr) : QObject(parent)
    {
        // Set up a timer to update the values every 1 second
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &SystemMonitor::updateData);
        timer->start(1000); // 1000 milliseconds = 1 second

        // Perform the initial data update
        updateData();
    }

    double cpuUsage() const { return m_cpuUsage; }
    double ramUsage() const { return m_ramUsage; }
    int temperature() const { return m_temperature; }

private slots:
    void updateData()
    {
        updateCpuUsage();
        updateRamUsage();
        updateTemperature();
    }

    void updateCpuUsage()
    {
        QFile file("/proc/stat");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Could not open /proc/stat";
            return;
        }

        QTextStream in(&file);
        QString line = in.readLine();
        file.close();

        QStringList parts = line.split(' ', Qt::SkipEmptyParts);
        if (parts.size() < 5) {
            qWarning() << "Invalid /proc/stat format";
            return;
        }

        quint64 user = parts[1].toULongLong();
        quint64 nice = parts[2].toULongLong();
        quint64 system = parts[3].toULongLong();
        quint64 idle = parts[4].toULongLong();
        quint64 iowait = parts[5].toULongLong();
        quint64 irq = parts[6].toULongLong();
        quint64 softirq = parts[7].toULongLong();
        quint64 steal = parts[8].toULongLong();
        quint64 total = user + nice + system + idle + iowait + irq + softirq + steal;

        if (m_lastCpuTotal == 0) {
            m_lastCpuTotal = total;
            m_lastCpuIdle = idle;
            return;
        }

        quint64 totalDiff = total - m_lastCpuTotal;
        quint64 idleDiff = idle - m_lastCpuIdle;

        double usage = 0.0;
        if (totalDiff > 0) {
            usage = 100.0 * (double)(totalDiff - idleDiff) / (double)totalDiff;
        }

        m_lastCpuTotal = total;
        m_lastCpuIdle = idle;

        if (m_cpuUsage != usage) {
            m_cpuUsage = usage;
            emit cpuUsageChanged();
        }
    }

    void updateRamUsage()
    {
        QFile file("/proc/meminfo");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Could not open /proc/meminfo";
            return;
        }

        QTextStream in(&file);
        quint64 memTotal = 0;
        quint64 memAvailable = 0;

        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.startsWith("MemTotal:")) {
                memTotal = line.split(' ', Qt::SkipEmptyParts)[1].toULongLong();
            } else if (line.startsWith("MemAvailable:")) {
                memAvailable = line.split(' ', Qt::SkipEmptyParts)[1].toULongLong();
            }
        }
        file.close();

        if (memTotal > 0) {
            double usage = 100.0 * (double)(memTotal - memAvailable) / (double)memTotal;
            if (m_ramUsage != usage) {
                m_ramUsage = usage;
                emit ramUsageChanged();
            }
        }
    }

    void updateTemperature()
    {
        QFile file("/sys/class/thermal/thermal_zone0/temp");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Could not open /sys/class/thermal/thermal_zone0/temp";
            m_temperature = -1; // Indicate an error
            emit temperatureChanged();
            return;
        }

        QTextStream in(&file);
        QString tempString = in.readAll();
        file.close();

        int temp = tempString.toInt() / 1000;

        if (m_temperature != temp) {
            m_temperature = temp;
            emit temperatureChanged();
        }
    }

signals:
    void cpuUsageChanged();
    void ramUsageChanged();
    void temperatureChanged();

private:
    double m_cpuUsage = 0.0;
    double m_ramUsage = 0.0;
    int m_temperature = 0;
    quint64 m_lastCpuTotal = 0;
    quint64 m_lastCpuIdle = 0;
};

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Register the C++ class to be accessible from QML
    qmlRegisterSingletonType<SystemMonitor>("com.example.sysmonitor", 1, 0, "SystemMonitor",
        [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject* {
            Q_UNUSED(engine);
            Q_UNUSED(scriptEngine);
            return new SystemMonitor();
        });

    const QUrl url(u"qrc:/sys-monitor/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

#include "main.moc"

