# Use CMAKE

FILE(GLOB TetrisShaders
  "${CMAKE_CURRENT_LIST_DIR}/static.frag"
  "${CMAKE_CURRENT_LIST_DIR}/static.vert"
)

target_sources(
Kodi-Engine PUBLIC
  ${TetrisShaders}
)

source_group("TetrisGame/Shaders" FILES ${TetrisShaders})
