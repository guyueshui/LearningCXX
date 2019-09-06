// see http://think-async.com/Asio/asio-1.12.2/doc/asio/tutorial/tuttimer1.html
#include <iostream>
#include "asio.hpp"

int main()
{
    asio::io_context io;
    asio::steady_timer t(io, asio::chrono::seconds(5));
    t.wait();
    std::cout << "after 5s, I print \"Hello World\"" << std::endl;
    return 0;
}
