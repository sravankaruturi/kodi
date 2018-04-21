FILE(GLOB Shaders
  "${CMAKE_CURRENT_LIST_DIR}/basic.frag"
  "${CMAKE_CURRENT_LIST_DIR}/basic.vert"
  "${CMAKE_CURRENT_LIST_DIR}/batchTexture.frag"
  "${CMAKE_CURRENT_LIST_DIR}/batchTexture.vert"
)

target_sources(
Kodi-Engine PRIVATE
  ${Shaders}
)

source_group("Shaders"  FILES   ${Shaders})
