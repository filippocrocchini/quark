
find_package(GLM REQUIRED)
find_package(SOIL2 REQUIRED)
find_package(ASSIMP REQUIRED)

file(GLOB QUARK_SOURCE_FILES *.cpp)
source_group(src FILES ${QUARK_SOURCE_FILES})

add_library(quark STATIC ${QUARK_SOURCE_FILES} ${INCLUDE_FILES})

find_package(OpenGL REQUIRED)
if(OpenGL_FOUND)
  target_link_libraries(quark ${OPENGL_gl_LIBRARY})
  target_include_directories(quark PUBLIC ${OPENGL_INCLUDE_DIR})
endif()

find_package(GLEW REQUIRED)
if(GLEW_FOUND)
  target_link_libraries(quark ${GLEW_LIBRARIES})
  target_include_directories(quark PUBLIC ${GLEW_INCLUDE_DIR})
  target_sources(quark PUBLIC ${GLEW_HEADERS})
endif()

find_package(GLFW3 REQUIRED)
if(GLFW3_FOUND)
  target_link_libraries(quark ${GLFW3_LIBRARIES})
  target_include_directories(quark PUBLIC ${GLFW3_INCLUDE_DIR})
  target_sources(quark PUBLIC ${GLFW3_HEADERS})
endif()

if(NOT WIN32)
    find_library(PTHREAD PATH_SUFFIXES lib lib64 NAMES pthread) 
    target_link_libraries(quark ${PTHREAD})
endif()
