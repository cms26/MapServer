cmake_minimum_required(VERSION 3.5)

project(MapServer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets HttpServer Location Quick Gui QuickWidgets QuickControls2 Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets HttpServer Location Quick Gui QuickWidgets QuickControls2 Charts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        interface/httpserver.cpp
        interface/httpserver.h
        map/mapitem.h
        map/mapitem.cpp
        map/mapitemfwd.h
        map/map.h
        map/map.cpp
        iconloader.h
        iconloader.cpp
        map/mapitemsmodel.cpp
        map/mapitemsmodel.h
        interface/earthquakeusgs.cpp
        interface/earthquakeusgs.h
        metadata/chartdisplay.cpp
        metadata/chartdisplay.h
        metadata/metadatadisplay.cpp
        metadata/metadatadisplay.h
        metadata/metadatadisplay.ui
)

set(RESOURCE_FILES resources.qrc)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MapServer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${RESOURCE_FILES}
    )

    qt_add_qml_module(MapServer
        URI map
        VERSION 1.0
        QML_FILES
        map/MapOverlay.qml
        map/MapItem.qml
        map/MapItemHistory.qml)

    include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/map
        ${CMAKE_CURRENT_SOURCE_DIR}/interface
        ${CMAKE_CURRENT_SOURCE_DIR}/metadata
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MapServer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MapServer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MapServer
            ${PROJECT_SOURCES}
            ${RESOURCE_FILES}
        )
    endif()
endif()

target_link_libraries(MapServer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets 
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::HttpServer
    Qt${QT_VERSION_MAJOR}::Location
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::QuickWidgets
    Qt${QT_VERSION_MAJOR}::QuickControls2
    Qt${QT_VERSION_MAJOR}::Charts)

set_target_properties(MapServer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS MapServer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MapServer)
endif()
