#ifndef SERVER_SERVER_HPP
#define SERVER_SERVER_HPP

#include <boost/asio.hpp>
#include <cstdint>
#include <memory>

#include "channel.h"

using boost::asio::ip::tcp;

class Server
{
   public:
    explicit Server() : channel(std::make_shared<Channel>()) {}

    void open(uint16_t port);
    void start();

   private:
    boost::asio::io_context io_context;
    std::unique_ptr<tcp::acceptor> acceptor;
    std::shared_ptr<Channel> channel;

    void accept();
};

#endif  // SERVER_SERVER_HPP
