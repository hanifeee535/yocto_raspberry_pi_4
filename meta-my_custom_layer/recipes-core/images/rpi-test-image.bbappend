

# Adding both QML application and helloworld application to the image.

IMAGE_INSTALL:append = " qtmlapp helloworld"

# adding graphics backend components for Qt.

DISTRO_FEATURES:append = " wayland "
IMAGE_INSTALL:append = " weston weston-init"

# Seting the default platform plugin for Qt applications.
QT_QPA_PLATFORM = "eglfs"
