#
# Find SOIL2
#
# This module defines the following variables:
# - SOIL2_INCLUDE_DIRS
# - SOIL2_FOUND
# - SOIL2_HEADERS
#
# The following variables can be set as arguments for the module.
# - SOIL2_ROOT_DIR : Root library directory of SOIL2
#
include(FindPackageHandleStandardArgs)

set(SOIL2_PATHS
  ${SOIL2_ROOT_DIR}
  ${QUARK_DEPENDENCIES}
)

find_path(SOIL2_INCLUDE_DIR SOIL2.h PATH_SUFFIXES include PATHS ${SOIL2_PATHS})

set(SOIL2_LIBRARY SOIL2_LIBRARY-NOTFOUND)
find_library(SOIL2_LIBRARY PATH_SUFFIXES lib lib64 NAMES soil2 PATHS ${SOIL2_PATHS})

find_package_handle_standard_args(SOIL2 DEFAULT_MSG SOIL2_INCLUDE_DIR SOIL2_LIBRARY)

if (SOIL2_FOUND)
	set(SOIL2_INCLUDE_DIRS ${SOIL2_INCLUDE_DIR})
  set(SOIL2_LIBRARIES ${SOIL2_LIBRARY})
  set(SOIL2_HEADERS ${SOIL2_INCLUDE_DIR}/SOIL2.h)
endif()

mark_as_advanced(SOIL2_INCLUDE_DIR SOIL2_LIBRARY SOIL2_PATHS)
