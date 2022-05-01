#ifndef SERVER_SERVER_HPP
#define SERVER_SERVER_HPP

#include <boost/asio.hpp>
#include <cstdint>
#include <memory>

#include "channel.hpp"

using boost::asio::ip::tcp;

class Server
{
  public:
    explicit Server(uint16_t port)
        : port(port), acceptor(io_context, tcp::endpoint(tcp::v4(), port)),
          channel(std::make_shared<Channel>())
    {
        accept();
    };

    void start();

  private:
    [[maybe_unused]] uint16_t port;
    boost::asio::io_context io_context;
    tcp::acceptor acceptor;
    std::shared_ptr<Channel> channel;

    void accept();
};

#endif // SERVER_SERVER_HPP
