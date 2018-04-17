FILE(GLOB GraphicsFiles
  "${CMAKE_CURRENT_LIST_DIR}/Window.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Window.h"
)

target_sources(
Kodi-Engine PRIVATE
  ${GraphicsFiles}
)

source_group("Core\\Graphics"   FILES   ${GraphicsFiles})
