aux_source_directory(. TEST_SRC)
add_executable(test ${TEST_SRC})
target_link_libraries(test PRIVATE Catch2Main Catch2 utils)