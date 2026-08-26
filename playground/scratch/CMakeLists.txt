file(GLOB demo_srcs *.cpp)
# message(STATUS "listing source...\n" ${demo_srcs})
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
add_library(_asan INTERFACE)
target_compile_options(_asan INTERFACE
    -O0 -g
    -fsanitize=address,leak
    -fno-omit-frame-pointer
)
target_link_options(_asan INTERFACE -fsanitize=address,leak)

target_link_libraries(test_my_vector PRIVATE _asan)
target_link_libraries(test_my_spsc PRIVATE _asan)
target_link_libraries(test_timer PRIVATE utils _asan)
target_link_libraries(test_logger PRIVATE utils _asan)
target_link_libraries(test_workthread PRIVATE utils _asan)
target_link_libraries(test_objpool PRIVATE _asan)
target_link_libraries(test_threadpool PRIVATE utils)

add_subdirectory(include)
add_subdirectory(unitest)