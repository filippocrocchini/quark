#
# Find GLEW
#
# This module defines the following variables:
# - GLEW_INCLUDE_DIRS
# - GLEW_FOUND
# - GLEW_HEADERS
# - GLEW_LIBRARIES
# The following variables can be set as arguments for the module.
# - GLEW_ROOT_DIR : Root library directory of GLEW
#
include(FindPackageHandleStandardArgs)

set(GLEW_PATHS
  ${GLEW_ROOT_DIR}
  ${QUARK_DEPENDENCIES}
)

find_path(GLEW_INCLUDE_DIR GLEW/glew.h GL/glew.h PATH_SUFFIXES include PATHS ${GLEW_PATHS})

 set(CMAKE_FIND_LIBRARY_PREFIXES "lib" "")
if(WIN32)
  set(CMAKE_FIND_LIBRARY_SUFFIXES ".dll")
  if(GLEW_STATIC)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
  endif(GLEW_STATIC)
else(WIN32)
  set(CMAKE_FIND_LIBRARY_SUFFIXES ".so")
  if(GLEW_STATIC)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
  endif(GLEW_STATIC)
endif()

set(GLEW_LIBRARY GLEW_LIBRARY-NOTFOUND)
find_library(GLEW_LIBRARY PATH_SUFFIXES lib lib64 NAMES glew glew32 GLEW PATHS ${GLEW_PATHS})

find_package_handle_standard_args(GLEW DEFAULT_MSG GLEW_INCLUDE_DIR GLEW_LIBRARY)

if (GLEW_FOUND)
	set(GLEW_INCLUDE_DIRS ${GLEW_INCLUDE_DIR})
  set(GLEW_LIBRARIES ${GLEW_LIBRARY})
  file(GLOB_RECURSE GLEW_HEADERS ${GLEW_INCLUDE_DIR}/*.hpp ${GLEW_INCLUDE_DIR}/*.h)
endif()

mark_as_advanced(GLEW_INCLUDE_DIR GLEW_LIBRARY GLEW_PATHS LIBRARY_NAME)
