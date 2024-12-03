#include <asio.hpp>
#include <asio/ip/address.hpp>
#include <asio/ip/basic_endpoint.hpp>
#include <asio/ip/detail/endpoint.hpp>
#include <asio/ip/tcp.hpp>

using asio::ip::tcp;

int main()
{
    asio::io_service io_service;
    tcp::socket socket(io_service);
    auto addr = asio::ip::make_address("127.0.0.1");
    asio::ip::tcp::endpoint ep(addr, 12306);
    socket.connect(ep);
}