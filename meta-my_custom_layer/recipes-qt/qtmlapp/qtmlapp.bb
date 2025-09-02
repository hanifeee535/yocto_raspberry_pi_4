SUMMARY = "Qt6 QML Application"
DESCRIPTION = "Sample Qt6 QML application for Raspberry Pi 4"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://main.cpp \
           file://main.qml \
           file://CMakeLists.txt"

S = "${WORKDIR}"

DEPENDS = "qtbase qtdeclarative"

inherit cmake qt6-cmake


QMAKE_QT_TOOLS = "${RECIPE_SYSROOT_NATIVE}/usr/libexec/qt6"
PATH:prepend = "${RECIPE_SYSROOT_NATIVE}/usr/bin:"


do_compile() {
    # Set the build environment variables directly for this command.
    export PATH="${RECIPE_SYSROOT_NATIVE}/usr/libexec/qt6:${RECIPE_SYSROOT_NATIVE}/usr/bin:${PATH}"
    
    # Run cmake to configure the build
    cmake -S ${S} -B ${B} \
        -DCMAKE_TOOLCHAIN_FILE=${OECORE_NATIVE_SYSROOT}/usr/share/cmake/OEToolchain.cmake \
        -DCMAKE_INSTALL_PREFIX=/usr \
        -DCMAKE_BUILD_TYPE=Release \
        -GNinja
    
    # Run the ninja build
    ninja -C ${B}
}

do_install() {
    # Now, install the built files
    install -d ${D}/usr/bin
    install -m 0755 ${B}/qtmlapp ${D}/usr/bin/
    
    # Install the QML directory
    install -d ${D}/usr/share/qml
    cp -r ${S}/qtmlapp/qml ${D}/usr/share/
}

FILES_${PN} = "/usr/bin/qtmlapp \
               /usr/share/qml/qtmlapp"
