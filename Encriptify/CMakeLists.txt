cmake_minimum_required(VERSION 3.16)

project(xTeaV3 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        backend.h
        backend.cpp
        xtea.h
        xtea.cpp
        interfaceForEncryption.h
        interfaceForEncryption.cpp
        interfaceForEncryption.ui
        interfaceForDecryption.h
        interfaceForDecryption.cpp
        interfaceForDecryption.ui
        resources.qrc
)

# Найти необходимые модули Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia MultimediaWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia MultimediaWidgets)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(xTeaV3
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(xTeaV3
        ${PROJECT_SOURCES}
    )
endif()

# Линковка библиотек
target_link_libraries(xTeaV3 PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::MultimediaWidgets
)

if(${QT_VERSION_MAJOR} EQUAL 6)
    qt_finalize_executable(xTeaV3)
endif()

include(GNUInstallDirs)
install(TARGETS xTeaV3
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
