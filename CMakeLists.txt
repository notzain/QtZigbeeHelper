cmake_minimum_required(VERSION 2.8.11)

project(qtzigbeehelper)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin) # http://stackoverflow.com/questions/18826789/cmake-output-build-directory
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

IF(WIN32)
    SET(GUI_TYPE WIN32)
ENDIF(WIN32)
IF (APPLE)
    SET(GUI_TYPE MACOSX_BUNDLE)
ENDIF (APPLE)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5SerialPort REQUIRED)

file(GLOB QtZigbeeHelper_SRC ${CMAKE_SOURCE_DIR}/src/*)
file(GLOB QtZigbeeHelper_UI ${CMAKE_SOURCE_DIR}/ui/*)

qt5_wrap_ui(QtZigbeeHelper_UI_H ${QtZigbeeHelper_UI})

add_executable(qtzigbeehelper ${GUI_TYPE} ${QtZigbeeHelper_SRC} ${QtZigbeeHelper_UI_H})
qt5_use_modules(qtzigbeehelper Widgets SerialPort Core)
target_link_libraries(qtzigbeehelper ${QT_LIBRARIES})
