#
# Find GLM
#
# This module defines the following variables:
# - GLM_INCLUDE_DIRS
# - GLM_FOUND
# - GLM_HEADERS
#
# The following variables can be set as arguments for the module.
# - GLM_ROOT_DIR : Root library directory of GLM
#
include(FindPackageHandleStandardArgs)

set(GLM_PATHS
  ${GLM_ROOT_DIR}
  ${QUARK_DEPENDENCIES}
)

find_path(GLM_INCLUDE_DIR glm/glm.hpp PATH_SUFFIXES include PATHS ${GLM_PATHS})

find_package_handle_standard_args(GLM DEFAULT_MSG GLM_INCLUDE_DIR)

if (GLM_FOUND)
	set(GLM_INCLUDE_DIRS ${GLM_INCLUDE_DIR})
  file(GLOB_RECURSE GLM_HEADERS ${GLM_INCLUDE_DIR}/*.hpp ${GLM_INCLUDE_DIR}/*.h)
endif()

mark_as_advanced(GLM_INCLUDE_DIR GLM_PATHS)
