cmake_minimum_required(VERSION 3.6)

project(Engine)

set(CMAKE_CXX_STANDARD 11)

set(LIB_FOLDER "libs" CACHE PATH "Path to the folder containing lib files. The default is libs/.")

set(ASSIMP_LIB_FOLDER "assimp/bin" CACHE PATH "Path to the folder containing ASSIMP dll files.")
set(GLEW_LIB_FOLDER "glew/bin" CACHE PATH "Path to the folder containing GLEW dll files.")
set(GLFW_LIB_FOLDER "glfw/bin" CACHE PATH "Path to the folder containing GLFW3 dll files.")

set(ASSIMP_INCLUDE_FOLDER "assimp/include" CACHE PATH "Path to the folder containing ASSIMP headers.")
set(GLEW_INCLUDE_FOLDER "glew/include" CACHE PATH "Path to the folder containing GLEW headers.")
set(GLFW_INCLUDE_FOLDER "glfw/include" CACHE PATH "Path to the folder containing GLFW headers.")
set(GLM_INCLUDE_FOLDER "glm/include" CACHE PATH "Path to the folder containing GLM headers.")

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES include/*.h)

set(ASSIMP_DLL "libassimp" CACHE STRING "Assimp library name.")
set(GLEW_DLL "libglew" CACHE STRING "Glew library name, usually libglew or glew32.")
set(GLFW_DLL "libglfw3" CACHE STRING "Glfw3 library name.")

include_directories("include")
include_directories("include/SOIL2")

include_directories(${LIB_FOLDER}/${ASSIMP_INCLUDE_FOLDER})
include_directories(${LIB_FOLDER}/${GLEW_INCLUDE_FOLDER})
include_directories(${LIB_FOLDER}/${GLFW_INCLUDE_FOLDER})
include_directories(${LIB_FOLDER}/${GLM_INCLUDE_FOLDER})

link_directories(${LIB_FOLDER}/${ASSIMP_LIB_FOLDER})
link_directories(${LIB_FOLDER}/${GLEW_LIB_FOLDER})
link_directories(${LIB_FOLDER}/${GLFW_LIB_FOLDER})

set(ASSIMP_DLL_FILE ${CMAKE_SOURCE_DIR}/${LIB_FOLDER}/${ASSIMP_LIB_FOLDER}/${ASSIMP_DLL}.dll)
set(GLEW_DLL_FILE ${CMAKE_SOURCE_DIR}/${LIB_FOLDER}/${GLEW_LIB_FOLDER}/${GLEW_DLL}.dll)
set(GLFW_DLL_FILE ${CMAKE_SOURCE_DIR}/${LIB_FOLDER}/${GLFW_LIB_FOLDER}/${GLFW_DLL}.dll)

if(EXISTS ${ASSIMP_DLL_FILE})
    configure_file(${ASSIMP_DLL_FILE} ${CMAKE_BINARY_DIR}/${ASSIMP_DLL}.dll COPYONLY)
else()
    message(${ASSIMP_DLL_FILE} " not found.")
endif()

if(EXISTS ${GLEW_DLL_FILE})
    configure_file(${GLEW_DLL_FILE} ${CMAKE_BINARY_DIR}/${GLEW_DLL}.dll COPYONLY)
else()
    message(${GLEW_DLL_FILE} " not found.")
endif()

if(EXISTS ${GLFW_DLL_FILE})
    configure_file(${GLFW_DLL_FILE} ${CMAKE_BINARY_DIR}/${GLFW_DLL}.dll COPYONLY)
else()
    message(${GLFW_DLL_FILE} " not found.")
endif()

add_executable(Engine ${SOURCE_FILES} ${INCLUDE_FILES})
target_link_libraries(Engine opengl32 ${ASSIMP_DLL} ${GLEW_DLL} ${GLFW_DLL})
