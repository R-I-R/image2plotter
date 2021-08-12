cmake_minimum_required(VERSION 3.5)

project(image2plotter LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

include_directories(./src)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Svg OpenGL LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Svg OpenGL LinguistTools REQUIRED)

set(TS_FILES)
set(SRCFORMS ./src/mainwindow.cpp)
set(SOURCES ./src/main.cpp ./src/svgViewer.cpp)
qt_wrap_ui(SOURCES ./src/mainwindow.ui)

add_executable(image2plotter ${SOURCES} ${SRCFORMS} ${TS_FILES})

target_link_libraries(image2plotter PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Svg Qt${QT_VERSION_MAJOR}::OpenGL)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
