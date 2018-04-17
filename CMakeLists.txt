# Use CMAKE
cmake_minimum_required (VERSION 2.6)
project (Kodi-Engine)

# Project Version Number
set (Kodi_VERSION_MAJOR 1)
set (Kodi_VERSION_MINOR 1)

#Configure a header file to pass some CMake Settings to the Source Code.
configure_file(
  "${PROJECT_SOURCE_DIR}/Source/KodiConfig.h.in"
  "${PROJECT_BINARY_DIR}/KodiConfig.h"
)

# Add the binary Directory to the Include Directories
include_directories("${PROJECT_BINARY_DIR}")

#WIN32 is necessary for a Windows Application. Other wise, it'd be treated as a console Application
add_executable(Kodi-Engine "")

include(Source/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/librarybinaries/CMakeLists.txt)

target_include_directories(Kodi-Engine PRIVATE ${PROJECT_SOURCE_DIR}/includes/)
