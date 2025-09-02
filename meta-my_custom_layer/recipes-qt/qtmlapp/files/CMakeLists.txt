cmake_minimum_required(VERSION 3.16)

# Set the project name and version.
project(qtmlapp VERSION 1.0)

# Set the C++ standard. This is required for modern Qt applications.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the necessary Qt6 components.
# This will find the modules needed for a QML application.
find_package(Qt6 6.4.3 REQUIRED COMPONENTS Quick)

# Use Qt's CMake functions for project setup and executable creation.
qt_standard_project_setup()

# Add the executable target.
# It includes the C++ and QML source files.
qt_add_executable(qtmlapp
    main.cpp
    main.qml
)

# Set the destination for the QML files.
# This ensures that the QML files are installed in a directory where the
# application can find them at runtime.
qt_add_qml_module(qtmlapp
    URI "qtmlapp"
    VERSION 1.0
    QML_FILES main.qml
)

# Install the executable to the standard binary directory.
install(TARGETS qtmlapp
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Optional: Add an RPATH to ensure the executable finds the libraries.
# This is often managed automatically by Yocto, but can be helpful for debugging.
set_target_properties(qtmlapp PROPERTIES
    QT_QML_DEPLOY_RUNTIME_PATH ${CMAKE_INSTALL_FULL_LIBDIR}
)
