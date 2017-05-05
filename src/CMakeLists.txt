
find_package(GLM REQUIRED)
find_package(SOIL2 REQUIRED)
find_package(ASSIMP REQUIRED)

file(GLOB QUARK_SOURCE_FILES ./*.cpp)
source_group(src ${QUARK_SOURCE_FILES})

add_executable(Quark ${QUARK_SOURCE_FILES} ${QUARK_INCLUDE_FILES})

find_package(OpenGL REQUIRED)
if(OpenGL_FOUND)
  target_link_libraries(Quark ${OPENGL_gl_LIBRARY})
  target_include_directories(Quark PUBLIC ${OPENGL_INCLUDE_DIR})
endif()

find_package(GLEW REQUIRED)
if(GLEW_FOUND)
  target_link_libraries(Quark ${GLEW_LIBRARIES})
  target_include_directories(Quark PUBLIC ${GLEW_INCLUDE_DIR})
  target_sources(Quark PUBLIC ${GLEW_HEADERS})
endif()

find_package(GLFW3 REQUIRED)
if(GLFW3_FOUND)
  target_link_libraries(Quark ${GLFW3_LIBRARIES})
  target_include_directories(Quark PUBLIC ${GLFW3_INCLUDE_DIR})
  target_sources(Quark PUBLIC ${GLFW3_HEADERS})
endif()
