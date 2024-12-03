// Cf. https://think-async.com/Asio/asio-1.22.1/doc/asio/tutorial/tuttimer4.html
#include <iostream>
#include <asio.hpp>

#define CONTAIN_EC true

#if CONTAIN_EC
namespace ph = std::placeholders;
#endif


class Printer
{
public:
    Printer(asio::io_context& io, int count)
        : count_(count),
          timer_(io, asio::chrono::seconds(1))
    {
        timer_.async_wait(std::bind(
            &Printer::print, this
#if CONTAIN_EC
            ,ph::_1
#endif
        ));
    }
    ~Printer() { std::cout << "Final count is " << count_ << std::endl;}

    void print(
#if CONTAIN_EC
        const asio::error_code& ec
#endif
        )
    {
        if (count_ < 5)
        {
            std::cout << count_ << std::endl;
            ++(count_);
            timer_.expires_at(timer_.expiry() + asio::chrono::seconds(1));
            timer_.async_wait(std::bind(
                &Printer::print, this
#if CONTAIN_EC
                ,ph::_1
#endif
            ));
        }
    }
private:
    int count_;
    asio::steady_timer timer_;
};

int main()
{
    asio::io_context io;
    Printer p(io, 0);
    io.run();
    return 0;
}