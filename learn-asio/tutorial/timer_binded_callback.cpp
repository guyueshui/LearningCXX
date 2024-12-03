// Cf. https://think-async.com/Asio/asio-1.22.1/doc/asio/tutorial/tuttimer3.html
#include <iostream>
#include <asio.hpp>

namespace ph = std::placeholders;

void print(const asio::error_code& ec, asio::steady_timer* t, int* count)
{
    if (*count < 5)
    {
        std::cout << *count << std::endl;
        ++(*count);
        t->expires_at(t->expiry() + asio::chrono::seconds(1));
        t->async_wait(std::bind(print, ph::_1, t, count));
    }
}

int main()
{
    asio::io_context io;
    int count = 0;
    asio::steady_timer t(io, asio::chrono::seconds(1));
    t.async_wait(std::bind(print, ph::_1, &t, &count));
    io.run();
    std::cout << "Final count is " << count << std::endl;
    return 0;
}