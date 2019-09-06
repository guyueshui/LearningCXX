// see: http://think-async.com/Asio/asio-1.12.2/doc/asio/tutorial/tuttimer3.html
#include <iostream>
#include <asio.hpp>
#include <boost/bind.hpp>

void print(const asio::error_code& /* e */,
           asio::steady_timer* t, int* count)
{
    if (*count < 5)
    {
        std::cout << *count << std::endl;
        ++(*count);
        t->expires_at(t->expiry() + asio::chrono::seconds(1));
        t->async_wait(boost::bind(
                    print, 
                    asio::placeholders::error, 
                    t, 
                    count));
    }
}

int main()
{
    asio::io_context io;
    int count = 0;
    asio::steady_timer t(io, asio::chrono::seconds(1));
    t.async_wait(boost::bind(
                print,
                asio::placeholders::error, 
                &t, 
                &count));
    io.run();
    std::cout << "Final count is " << count << std::endl;
    return 0;
}
