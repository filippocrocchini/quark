cmake_minimum_required(VERSION 3.6)
project(Quark)

set(QUARK_BUILD_TESTS ON CACHE BOOL "Build tests for Quark library.")
set(QUARK_BUILD_SHARED_LIB OFF CACHE BOOL "Build shared library.")
set(QUARK_USE_CUSTOM_LIBRARY_FOLDER OFF CACHE BOOL "Use custom folder for dependencies.")
set(ASSIMP_STATIC OFF CACHE BOOL "Use static library version of assimp.")
set(GLEW_STATIC OFF CACHE BOOL "Use static library version of glew.")
set(GLFW_STATIC OFF CACHE BOOL "Use static library version of glfw.")

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake-modules)

if(WIN32 OR USE_CUSTOM_LIBRARY_FOLDER)
  set(QUARK_DEPENDENCIES ${CMAKE_SOURCE_DIR}/dependencies)
endif()

add_subdirectory(include)
include_directories(include)

add_subdirectory(src)

if(QUARK_BUILD_TESTS)
	enable_testing()
    add_subdirectory(test)
endif(QUARK_BUILD_TESTS)
