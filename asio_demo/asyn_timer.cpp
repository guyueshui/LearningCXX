// see: http://think-async.com/Asio/asio-1.12.2/doc/asio/tutorial/tuttimer2.html
// note: compile with -lpthread or -pthread
#include <iostream>
#include "asio.hpp"

void print(const asio::error_code&)
{
    std::cout << "callback handler" << std::endl;
}

int main()
{
    asio::io_context io;
    asio::steady_timer t(io, asio::chrono::seconds(5));
    t.async_wait(print);
    std::cout << "before run" << std::endl;
    io.run();
    std::cout << "after run" << std::endl;
    return 0;
}
