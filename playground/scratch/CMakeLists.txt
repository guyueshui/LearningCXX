file(GLOB demo_srcs *.cpp)
message(STATUS "listing source...\n" list ${demo_srcs})
foreach(srcfile IN LISTS demo_srcs)
    get_filename_component(elfname ${srcfile} NAME_WE)
    message(STATUS "compile ${srcfile} ..to.. ${elfname}")
    add_executable(${elfname} ${srcfile})
endforeach()

# 引用了自定义头文件的要带上其源文件一起编译
aux_source_directory(include lib_srcs)
target_sources(balance-tree PUBLIC ${lib_srcs})
target_link_libraries(vtest utils)

# use asan to detect memory leak
target_compile_options(test_my_vector PRIVATE
    -O0 -g
    -fsanitize=address
    -fno-omit-frame-pointer
)
target_link_options(test_my_vector PRIVATE -fsanitize=address)

add_subdirectory(include)