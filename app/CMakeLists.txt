project(App)

get_property(QUARK_INCLUDE_FILES DIRECTORY ${CMAKE_SOURCE_DIR}/include PROPERTY QUARK_INCLUDE_FILES)

file(GLOB APP_SOURCE_FILES src/*.cpp)
file(GLOB APP_INCLUDE_FILES include/*.h)

include_directories(include)

add_executable(App ${APP_SOURCE_FILES} ${QUARK_INCLUDE_FILES} ${APP_INCLUDE_FILES})
target_link_libraries(App quark)

install(DIRECTORY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
