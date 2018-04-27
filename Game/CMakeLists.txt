# Use CMAKE

include("${CMAKE_CURRENT_LIST_DIR}/Shaders/CMakeLists.txt")

FILE(GLOB GameFiles
  "${CMAKE_CURRENT_LIST_DIR}/main.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Game.cpp"
)

target_sources(
Kodi-Engine PUBLIC
  ${GameFiles}
)

source_group("Game" FILES ${GameFiles})
