

FILE(GLOB GraphicsFiles
  "${CMAKE_CURRENT_LIST_DIR}/Window.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Window.h"
  "${CMAKE_CURRENT_LIST_DIR}/Shader.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Shader.h"
  "${CMAKE_CURRENT_LIST_DIR}/stb_image.h"
  "${CMAKE_CURRENT_LIST_DIR}/Texture.h"
  "${CMAKE_CURRENT_LIST_DIR}/Texture.cpp"
)

target_sources(
Kodi-Engine PRIVATE
  ${GraphicsFiles}
)

source_group("Core\\Graphics"   FILES   ${GraphicsFiles})
