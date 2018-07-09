cmake_minimum_required(VERSION 3.10)
project(Cupola)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

find_package(Libgit2 REQUIRED)

find_package(Qt5 COMPONENTS Qml Quick Core REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

qt5_add_resources(QT_RESOURCES src/qml.qrc)

add_executable(Cupola src/main.cpp ${QT_RESOURCES})
target_include_directories(Cupola PRIVATE ${LIBGIT2_INCLUDE_DIR})
target_link_libraries(Cupola ${LIBGIT2_LIBRARIES})
qt5_use_modules(Cupola Widgets Quick Core Qml)
