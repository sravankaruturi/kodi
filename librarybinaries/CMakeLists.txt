target_link_libraries(Kodi-Engine opengl32)
target_link_libraries(Kodi-Engine ${CMAKE_CURRENT_LIST_DIR}/GLEW/glew32s.lib)
target_link_libraries(Kodi-Engine ${CMAKE_CURRENT_LIST_DIR}/GLFW/glfw3.lib)

target_compile_definitions(Kodi-Engine PRIVATE GLEW_STATIC=1)
