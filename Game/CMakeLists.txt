# Use CMAKE

include("${CMAKE_CURRENT_LIST_DIR}/Shaders/CMakeLists.txt")

FILE(GLOB TetrisGame
  "${CMAKE_CURRENT_LIST_DIR}/main.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/TetrisGame.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/TetrisGame.h"
)

target_sources(
Kodi-Engine PUBLIC
  ${TetrisGame}
)

source_group("TetrisGame" FILES ${TetrisGame})
