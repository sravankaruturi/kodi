
FILE(GLOB BufferFiles
  "${CMAKE_CURRENT_LIST_DIR}/Buffer.h"
  "${CMAKE_CURRENT_LIST_DIR}/Buffer.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/IndexBuffer.h"
  "${CMAKE_CURRENT_LIST_DIR}/IndexBuffer.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/VertexArray.h"
  "${CMAKE_CURRENT_LIST_DIR}/VertexArray.cpp"
)

target_sources(
Kodi-Engine PRIVATE
  ${BufferFiles}
)

source_group("Core\\Graphics\\Buffers"   FILES   ${BufferFiles})
