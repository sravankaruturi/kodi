include(${CMAKE_CURRENT_LIST_DIR}/Graphics/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/Math/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/Shaders/CMakeLists.txt)

FILE(GLOB RootSource
  "${CMAKE_CURRENT_LIST_DIR}/main.cpp"
)

target_sources(
Kodi-Engine PRIVATE
  ${RootSource}
)
