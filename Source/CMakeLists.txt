include(${CMAKE_CURRENT_LIST_DIR}/Graphics/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/Math/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/Shaders/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/Utils/CMakeLists.txt)



FILE(GLOB RootSource
  "${CMAKE_CURRENT_LIST_DIR}/main.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/TileLayer.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/TileLayer.h"
	"${CMAKE_CURRENT_LIST_DIR}/Kodi.h"
)

# file(GLOB_RECURSE freetype_source_list "${CMAKE_CURRENT_LIST_DIR}/external_libraries/freetype/src/*.c" "${CMAKE_CURRENT_LIST_DIR}/external_libraries/freetype/*.h")
# file(GLOB freetype_gl_source_list "${CMAKE_CURRENT_LIST_DIR}/external_libraries/freetype-gl/*.c" "${CMAKE_CURRENT_LIST_DIR}/external_libraries/freetype-gl/*.h")

target_sources(
Kodi-Engine PRIVATE
  ${RootSource}
)

# target_sources(Kodi-Engine PRIVATE  ${freetype_source_list} )

# target_sources(Kodi-Engine PRIVATE  ${freetype_gl_source_list})

# source_group("External Libraries\\FreeType"      FILES   ${freetype_source_list})
# source_group("External Libraries\\FreeTypeGL"    FILES   ${freetype_gl_source_list})
