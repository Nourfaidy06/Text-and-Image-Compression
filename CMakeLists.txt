cmake_minimum_required(VERSION 3.16)

project(compressed_files VERSION 0.1 LANGUAGES CXX)

# Standard Qt automation settings
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Use C++17 as requested
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt 6 (or 5) components
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# --- Define all project files here ---
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    huffman.cpp    # Added backend implementation
    huffman.h      # Added backend header
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    # Qt 6 specific executable creation
    qt_add_executable(compressed_files
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    # Fallback for Qt 5 or Android
    if(ANDROID)
        add_library(compressed_files SHARED ${PROJECT_SOURCES})
    else()
        add_executable(compressed_files ${PROJECT_SOURCES})
    endif()
endif()

# Link the Qt Widgets library
target_link_libraries(compressed_files PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Platform specific configurations
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.compressed_files)
endif()

set_target_properties(compressed_files PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Standard Installation rules
include(GNUInstallDirs)
install(TARGETS compressed_files
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(compressed_files)
endif()
