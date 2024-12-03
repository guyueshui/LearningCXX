#include <iostream>
#include <asio.hpp>

void print(const asio::error_code& /*e*/)
{
  std::cout << "Hello, world!" << std::endl;
}

int main()
{
    asio::io_context io;
    asio::steady_timer t(io, asio::chrono::seconds(5));
    asio::steady_timer t2(io, asio::chrono::seconds(3));
    t.async_wait(&print);
    t2.async_wait([](const asio::error_code&){ std::cout << __func__ << std::endl; });
    std::cout << "before io.run\n";
    io.run();   // this blocks
    std::cout << "after return\n";
    return 0;
}