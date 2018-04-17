FILE(GLOB MathFiles
  "${CMAKE_CURRENT_LIST_DIR}/vec2.h"
  "${CMAKE_CURRENT_LIST_DIR}/vec2.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/vec3.h"
  "${CMAKE_CURRENT_LIST_DIR}/vec3.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/vec4.h"
  "${CMAKE_CURRENT_LIST_DIR}/vec4.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Math.h"
)

target_sources(
Kodi-Engine PRIVATE
  ${MathFiles}
)

source_group("Core\\Math"    FILES   ${MathFiles})
