add_library(utils SHARED utils.cpp my-timer.cpp simple_log.cpp thread_pool.cpp)
# target_compile_definitions(utils PUBLIC YDEBUG)