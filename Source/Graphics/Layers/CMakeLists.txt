

FILE(GLOB LayerFiles
  "${CMAKE_CURRENT_LIST_DIR}/Group.h"
  "${CMAKE_CURRENT_LIST_DIR}/Group.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Layer.h"
  "${CMAKE_CURRENT_LIST_DIR}/Layer.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/TileLayer.h"
  "${CMAKE_CURRENT_LIST_DIR}/TileLayer.cpp"
)

target_sources(
Kodi-Engine PRIVATE
  ${LayerFiles}
)

source_group("Core\\Graphics\\Layers"   FILES   ${LayerFiles})
