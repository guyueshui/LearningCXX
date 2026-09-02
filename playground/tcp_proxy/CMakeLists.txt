add_executable(tcproxy
    main.cpp
    config_read.cpp
    sniff_session.cpp
    route.cpp
    )
target_link_libraries(tcproxy PRIVATE utils yaml-cpp)