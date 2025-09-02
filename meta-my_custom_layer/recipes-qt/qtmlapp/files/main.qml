import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("System Monitor")

    SystemMonitor {
        id: monitor
    }

    // A simple, dark theme to make the text readable
    color: "#222222"

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 20

        // Title
        Text {
            Layout.alignment: Qt.AlignHCenter
            text: "Raspberry Pi System Status"
            font.pixelSize: 24
            color: "white"
        }

        // CPU Usage Section
        GroupBox {
            Layout.fillWidth: true
            title: "CPU Load"
            font.pixelSize: 18
            contentItem: ColumnLayout {
                spacing: 10
                Text {
                    text: `CPU Usage: ${monitor.cpuUsage.toFixed(1)}%`
                    color: "white"
                }
                ProgressBar {
                    Layout.fillWidth: true
                    value: monitor.cpuUsage / 100
                    background: Rectangle {
                        color: "#444"
                        radius: 5
                    }
                    contentItem: Rectangle {
                        color: "#00aaff"
                        radius: 5
                        width: parent.width
                    }
                }
            }
        }

        // Temperature Section
        GroupBox {
            Layout.fillWidth: true
            title: "Temperature"
            font.pixelSize: 18
            contentItem: ColumnLayout {
                spacing: 10
                Text {
                    text: `Temperature: ${monitor.temperature}°C`
                    color: "white"
                }
                ProgressBar {
                    Layout.fillWidth: true
                    value: monitor.temperature / 100 // assuming max temp is 100
                    background: Rectangle {
                        color: "#444"
                        radius: 5
                    }
                    contentItem: Rectangle {
                        color: "#ff8c00" // Orange
                        radius: 5
                        width: parent.width
                    }
                }
            }
        }

        // RAM Usage Section
        GroupBox {
            Layout.fillWidth: true
            title: "RAM Usage"
            font.pixelSize: 18
            contentItem: ColumnLayout {
                spacing: 10
                Text {
                    text: `RAM Usage: ${monitor.ramUsage.toFixed(1)}%`
                    color: "white"
                }
                ProgressBar {
                    Layout.fillWidth: true
                    value: monitor.ramUsage / 100
                    background: Rectangle {
                        color: "#444"
                        radius: 5
                    }
                    contentItem: Rectangle {
                        color: "#00ff7f" // SpringGreen
                        radius: 5
                        width: parent.width
                    }
                }
            }
        }
    }
}

