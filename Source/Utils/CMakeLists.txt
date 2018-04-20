
FILE(GLOB UtilsSource
  "${CMAKE_CURRENT_LIST_DIR}/fileUtils.h"
  "${CMAKE_CURRENT_LIST_DIR}/Timer.h"
  "${CMAKE_CURRENT_LIST_DIR}/GeneralUtils.h"
)

target_sources(
Kodi-Engine PRIVATE
  ${UtilsSource}
)

source_group("Core\\Utils"    FILES   ${UtilsSource})
