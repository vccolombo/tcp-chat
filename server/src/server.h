#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include <boost/asio.hpp>
#include <cstdint>
#include <memory>

#include "connectionfactory.h"

using boost::asio::ip::tcp;

class Server
{
   public:
    explicit Server(std::unique_ptr<ConnectionFactory> connection_factory)
        : _connection_factory(std::move(connection_factory)){};

    void open(uint16_t port);
    void start();

   private:
    boost::asio::io_context _io_context;
    std::unique_ptr<tcp::acceptor> _acceptor;
    std::unique_ptr<ConnectionFactory> _connection_factory;

    void accept();
};

#endif  // SERVER_SERVER_H
