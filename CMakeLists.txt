cmake_minimum_required(VERSION 3.6)

project(Engine)

set(CMAKE_CXX_STANDARD 11)

set(ASSIMP_LIB_FOLDER "libs/assimp/bin" CACHE PATH "Path to the folder containing ASSIMP lib files.")
set(GLEW_LIB_FOLDER "libs/glew/bin" CACHE PATH "Path to the folder containing GLEW lib files.")
set(GLFW_LIB_FOLDER "libs/glfw/bin" CACHE PATH "Path to the folder containing GLFW3 lib files.")

set(ASSIMP_INCLUDE_FOLDER "libs/assimp/include" CACHE PATH "Path to the folder containing ASSIMP headers.")
set(GLEW_INCLUDE_FOLDER "libs/glew/include" CACHE PATH "Path to the folder containing GLEW headers.")
set(GLFW_INCLUDE_FOLDER "libs/glfw/include" CACHE PATH "Path to the folder containing GLFW headers.")

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES include/*.h)

set(ASSIMP_DLL "assimp" CACHE STRING "Assimp library name.")
set(GLEW_DLL "glew32" CACHE STRING "Glew library name, usually libglew or glew32.")
set(GLFW_DLL "glfw3" CACHE STRING "Glfw3 library name.")

include_directories(include)
include_directories(${ASSIMP_INCLUDE_FOLDER})
include_directories(${GLEW_INCLUDE_FOLDER})
include_directories(${GLFW_INCLUDE_FOLDER})

link_directories(${ASSIMP_LIB_FOLDER})
link_directories(${GLEW_LIB_FOLDER})
link_directories(${GLFW_LIB_FOLDER})

set(ASSIMP_DLL_FILE ${CMAKE_SOURCE_DIR}/${ASSIMP_LIB_FOLDER}/${ASSIMP_DLL}.dll)
set(GLEW_DLL_FILE ${CMAKE_SOURCE_DIR}/${GLEW_LIB_FOLDER}/${GLEW_DLL}.dll)
set(GLFW_DLL_FILE ${CMAKE_SOURCE_DIR}/${GLFW_LIB_FOLDER}/${GLFW_DLL}.dll)

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

add_executable(Engine ${SOURCE_FILES})
target_link_libraries(Engine opengl32 ${ASSIMP_DLL} ${GLEW_DLL} ${GLFW_DLL})

