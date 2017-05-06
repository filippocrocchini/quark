
file(GLOB QUARK_TESTS *.cpp)
source_group(src FILES ${QUARK_TESTS})

get_property(QUARK_INCLUDE_FILES DIRECTORY ${CMAKE_SOURCE_DIR}/include PROPERTY QUARK_INCLUDE_FILES) 
add_executable(quark_test ${QUARK_TESTS} ${QUARK_INCLUDE_FILES})
target_link_libraries(quark_test quark)

find_package(GTEST REQUIRED)
if(GTEST_FOUND)
  target_link_libraries(quark_test ${GTEST_LIBRARIES})
  target_include_directories(quark_test PUBLIC ${GTEST_INCLUDE_DIR})
  target_sources(quark_test PUBLIC ${GTEST_HEADERS})
endif()