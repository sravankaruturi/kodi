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


add_executable(Kodi-Engine "")


################### Include Directories ###################
target_include_directories(Kodi-Engine PRIVATE ${PROJECT_SOURCE_DIR}/includes/)
target_include_directories(Kodi-Engine PRIVATE ${PROJECT_SOURCE_DIR}/includes/Freetype/)
include_directories("${PROJECT_BINARY_DIR}")


# Gorilla Audio Stuff
file(GLOB_RECURSE
gorilla_audio_source_files
"${PROJECT_SOURCE_DIR}/Source/external_libraries/gorilla_audio/src/*.c"
"${PROJECT_SOURCE_DIR}/Source/external_libraries/gorilla_audio/src/*.h"
)

# target_sources(Kodi-Engine  PRIVATE ${gorilla_audio_source_files})
# source_group("External Libraries\\Gorilla Audio" FILES ${gorilla_audio_source_files})

# target_include_directories(Kodi-Engine PRIVATE ${PROJECT_SOURCE_DIR}/Source/external_libraries/gorilla_audio/include/)
# target_include_directories(Kodi-Engine PRIVATE ${PROJECT_SOURCE_DIR}/Source/external_libraries/gorilla_audio/ext/libogg/include/)
# target_include_directories(Kodi-Engine PRIVATE ${PROJECT_SOURCE_DIR}/Source/external_libraries/gorilla_audio/ext/libvorbis/include/)
# target_include_directories(Kodi-Engine PRIVATE ${PROJECT_SOURCE_DIR}/Source/external_libraries/gorilla_audio/ext/OpenAL/include/)


################### All Folders ###################
include(Source/CMakeLists.txt)
include(Source/Graphics/Buffers/CMakeLists.txt)
include(Source/Graphics/Layers/CMakeLists.txt)
include(Source/Graphics/Renderables/CMakeLists.txt)
include(Source/Graphics/Renderers/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/Game/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/librarybinaries/CMakeLists.txt)

include(Game/CMakeLists.txt)

################### Preprocessor Definitions ###################
target_compile_definitions(Kodi-Engine PRIVATE _CRT_SECURE_NO_WARNINGS=1)
target_compile_definitions(Kodi-Engine PRIVATE KODI_THROW_EXCEPTIONS=0)

# This is for FreeType
# target_compile_definitions(Kodi-Engine PRIVATE FT2_BUILD_LIBRARY)
# target_compile_definitions(Kodi-Engine PRIVATE _LIB)


################### Documentation / Specification ###################
# All the ints shall be int32_t
