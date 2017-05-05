cmake_minimum_required(VERSION 3.6)
project(Quark)

set(QUARK_RUN_TESTS OFF CACHE BOOL "Run tests for Quark library.")
set(QUARK_BUILD_SHARED_LIB OFF CACHE BOOL "Build shared library.")
set(QUARK_USE_CUSTOM_LIBRARY_FOLDER OFF CACHE BOOL "Use custom folder for dependencies.")
set(ASSIMP_STATIC OFF CACHE BOOL "Use static library version of assimp.")
set(GLEW_STATIC OFF CACHE BOOL "Use static library version of glew.")

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake-modules)

if(WIN32 OR USE_CUSTOM_LIBRARY_FOLDER)
  set(QUARK_DEPENDENCIES ${CMAKE_SOURCE_DIR}/dependencies)
endif()

file(GLOB QUARK_INCLUDE_FILES ./include/*.h)
source_group(include ${QUARK_INCLUDE_FILES})

add_subdirectory(src)

if(RUN_TESTS)
  add_subdirectory(test)
endif(RUN_TESTS)
