get_property(QUARK_INCLUDE_FILES DIRECTORY ${CMAKE_SOURCE_DIR}/include PROPERTY QUARK_INCLUDE_FILES)

function(createTest NAME)
	if(QUARK_BUILD_TESTS)
		set(SAMPLE_NAME test-${NAME})
		add_executable(${SAMPLE_NAME} ${NAME}.cpp ${QUARK_INCLUDE_FILES})
		target_link_libraries(${SAMPLE_NAME} quark)

		add_test( NAME ${SAMPLE_NAME} COMMAND $<TARGET_FILE:${SAMPLE_NAME}> )
	endif(QUARK_BUILD_TESTS)
endfunction()

add_subdirectory(basic)
add_subdirectory(looping_thread)
