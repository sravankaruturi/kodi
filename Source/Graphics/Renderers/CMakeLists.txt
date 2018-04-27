

FILE(GLOB RendererFiles
  "${CMAKE_CURRENT_LIST_DIR}/Renderer2D.h"
  "${CMAKE_CURRENT_LIST_DIR}/BatchRenderer2D.h"
  "${CMAKE_CURRENT_LIST_DIR}/BatchRenderer2D.cpp"
)

target_sources(
Kodi-Engine PRIVATE
  ${RendererFiles}
)

source_group("Core\\Graphics\\Renderers"   FILES   ${RendererFiles})
