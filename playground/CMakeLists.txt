cmake_minimum_required(VERSION 3.20)
project(scratch)

message(STATUS "CMake version: " ${CMAKE_VERSION})
if(NOT ${CMAKE_VERSION} VERSION_LESS "3.2")
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
else()
    message(STATUS "Checking compiler flags for C++11 support.")
    # Set C++11 support flags for various compilers
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag("-std=c++17" COMPILER_SUPPORTS_CXX17)
    check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
    if(COMPILER_SUPPORTS_CXX17)
        message(STATUS "C++17 is supported.")
        if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -stdlib=libc++")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
        endif()
    elseif(COMPILER_SUPPORTS_CXX0X)
        message(STATUS "C++0x is supported.")
        if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -stdlib=libc++")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
        endif()
    else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++17 support. Please use a different C++ compiler.")
    endif()
endif()


 
# 禁止 C++ assert terminate 程序
# add_definitions(-DNDEBUG)

# ASIO 不使用 Boost 库
#add_definitions(-DASIO_STANDALONE)

# Spdlog 使用外部 Fmt 库
#add_definitions(-DSPDLOG_FMT_EXTERNAL)

# Jwt-cpp 使用外部 Json 库
# ADD_DEFINITIONS(-DJWT_CPP_JSON_EXTERNAL)

# add_definitions(-DGLOG_ON)

# 生成编译命令文件，给 clangd 使用
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-g)

#设置输出目录
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/)

#加入包含目录
include_directories(${CMAKE_SOURCE_DIR}/scratch/include) 


#静态库目录
#link_directories(/usr/lib64/mysql)

#logger lib 
#add_subdirectory(log)

file(GLOB demo_srcs scratch/*.cpp)
message(STATUS "listing source...\n" list ${demo_srcs})
foreach(srcfile IN LISTS demo_srcs)
    get_filename_component(elfname ${srcfile} NAME_WE)
    message(STATUS "compile ${srcfile} ..to.. ${elfname}")
    add_executable(${elfname} ${srcfile})
endforeach()

# 引用了自定义头文件的要带上其源文件一起编译
aux_source_directory(scratch/include lib_srcs)
target_sources(balance-tree PUBLIC ${lib_srcs})


# aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRCS) #加入目录下所有源码
# add_executable(demo ${SRCS}) #生成可执行文件
# target_link_libraries(demo logger)  #链接 logger 库


# aux_source_directory(test_link test_link_src)
# add_executable(test_link ${test_link_src})
#: or we can use subdirectory
add_subdirectory(test_link)
