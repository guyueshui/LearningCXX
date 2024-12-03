// https://think-async.com/Asio/asio-1.22.1/doc/asio/tutorial/tuttimer5.html
#include <asio/io_context.hpp>
#include <iostream>
#include <asio.hpp>
#include <boost/bind/bind.hpp>


class Printer
{
public:
    Printer(asio::io_context& io)
        : count_(0),
          timer1_(io, asio::chrono::seconds(1)),
          timer2_(io, asio::chrono::seconds(1)),
          strand_(asio::make_strand(io))
    {
        timer1_.async_wait(asio::bind_executor(strand_, std::bind(&Printer::print1, this)));
        timer2_.async_wait(asio::bind_executor(strand_, std::bind(&Printer::print2, this)));
    }
    ~Printer() { std::cout << "Final count is " << count_ << std::endl; }

    void print1()
    {
        if (count_ < 10)
        {
            std::cout << "Timer1: " << count_ << std::endl;
            ++count_;
            timer1_.expires_at(timer1_.expiry() + asio::chrono::seconds(1));
            timer1_.async_wait(std::bind(&Printer::print1, this));
        }
    }

    void print2()
    {
        if (count_ < 10)
        {
            std::cout << "Timer2: " << count_ << std::endl;
            ++count_;
            timer2_.expires_at(timer2_.expiry() + asio::chrono::seconds(1));
            timer2_.async_wait(std::bind(&Printer::print2, this));
        }
    }

private:
    int count_;
    asio::steady_timer timer1_, timer2_;
    asio::strand<asio::io_context::executor_type> strand_;
};


int main()
{
    asio::io_context io;
    Printer p(io);
    asio::thread t([&io]() { io.run(); });
    auto f = std::bind(&asio::io_context::run, std::forward<asio::io_context*>(&io));
    auto g = std::bind(&Printer::print1, &p);
    boost::bind(&Printer::print2, &p);
    boost::bind(&asio::io_context::run, &io);
    io.run();
    t.join();
    return 0;
}