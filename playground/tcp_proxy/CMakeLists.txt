add_executable(tcproxy
    main.cpp
    sniff_session.cpp
    )
target_link_libraries(tcproxy PRIVATE utils)