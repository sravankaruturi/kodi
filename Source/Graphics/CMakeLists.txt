

FILE(GLOB GraphicsFiles
  "${CMAKE_CURRENT_LIST_DIR}/Window.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Window.h"
  "${CMAKE_CURRENT_LIST_DIR}/Shader.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Shader.h"
  "${CMAKE_CURRENT_LIST_DIR}/Renderable2D.h"
  "${CMAKE_CURRENT_LIST_DIR}/Simple2DRenderer.h"
  "${CMAKE_CURRENT_LIST_DIR}/Simple2DRenderer.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/BatchRenderer2D.h"
  "${CMAKE_CURRENT_LIST_DIR}/BatchRenderer2D.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Sprite.h"
  "${CMAKE_CURRENT_LIST_DIR}/Sprite.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/StaticSprite.h"
  "${CMAKE_CURRENT_LIST_DIR}/StaticSprite.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Layer.h"
  "${CMAKE_CURRENT_LIST_DIR}/Layer.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/TileLayer.h"
  "${CMAKE_CURRENT_LIST_DIR}/TileLayer.cpp"
)

target_sources(
Kodi-Engine PRIVATE
  ${GraphicsFiles}
)

source_group("Core\\Graphics"   FILES   ${GraphicsFiles})
