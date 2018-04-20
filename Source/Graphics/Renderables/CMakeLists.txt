

FILE(GLOB RenderableFiles
  "${CMAKE_CURRENT_LIST_DIR}/Renderable2D.h"
  "${CMAKE_CURRENT_LIST_DIR}/Sprite.h"
  "${CMAKE_CURRENT_LIST_DIR}/Sprite.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/StaticSprite.h"
  "${CMAKE_CURRENT_LIST_DIR}/StaticSprite.cpp"
)

target_sources(
Kodi-Engine PRIVATE
  ${RenderableFiles}
)

source_group("Core\\Graphics\\Renderables"   FILES   ${RenderableFiles})
