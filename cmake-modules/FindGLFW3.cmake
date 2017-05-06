#
# Find GLFW3
#
# This module defines the following variables:
# - GLFW3_INCLUDE_DIRS
# - GLFW3_FOUND
# - GLFW3_HEADERS
#
# The following variables can be set as arguments for the module.
# - GLFW3_ROOT_DIR : Root library directory of GLFW3
#
include(FindPackageHandleStandardArgs)

set(GLFW3_PATHS
  ${GLFW3_ROOT_DIR}
  ${QUARK_DEPENDENCIES}
)

find_path(GLFW3_INCLUDE_DIR GLFW/glfw3.h PATH_SUFFIXES include PATHS ${GLFW3_PATHS})

  set(CMAKE_FIND_LIBRARY_PREFIXES "lib"  "")
if(WIN32)
  set(CMAKE_FIND_LIBRARY_SUFFIXES ".dll")
  if(GLFW_STATIC)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
  endif(GLFW_STATIC)
else(WIN32)
  set(CMAKE_FIND_LIBRARY_SUFFIXES ".so")
  if(GLFW_STATIC)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
  endif(GLFW_STATIC)
endif()

set(GLFW3_LIBRARY GLFW3_LIBRARY-NOTFOUND)
find_library(GLFW3_LIBRARY PATH_SUFFIXES lib lib64 NAMES glfw3 glfw PATHS ${GLFW3_PATHS})

find_package_handle_standard_args(GLFW3 DEFAULT_MSG GLFW3_INCLUDE_DIR GLFW3_LIBRARY)

if (GLFW3_FOUND)
	set(GLFW3_INCLUDE_DIRS ${GLFW3_INCLUDE_DIR})
  set(GLFW3_LIBRARIES ${GLFW3_LIBRARY})
  file(GLOB_RECURSE GLFW3_HEADERS ${GLFW3_INCLUDE_DIR}/*.hpp ${GLFW3_INCLUDE_DIR}/*.h)
endif()

mark_as_advanced(GLFW3_INCLUDE_DIR GLFW3_LIBRARY GLFW3_PATHS)
