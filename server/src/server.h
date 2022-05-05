#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include <boost/asio.hpp>
#include <cstdint>
#include <memory>

using boost::asio::ip::tcp;

template <typename ConnectionType>
class Server
{
   public:
    void open(uint16_t port);
    void start();

   private:
    boost::asio::io_context _io_context;
    std::unique_ptr<tcp::acceptor> _acceptor;

    void accept();
};

// definition of template methods have to be in the header
// c++ can be a pain sometimes :/

template <typename ConnectionType>
void Server<ConnectionType>::open(uint16_t port)
{
    _acceptor = std::make_unique<tcp::acceptor>(
        _io_context, tcp::endpoint(tcp::v4(), port));
    accept();
}

template <typename ConnectionType>
void Server<ConnectionType>::start()
{
    _io_context.run();
}

template <typename ConnectionType>
void Server<ConnectionType>::accept()
{
    if (_acceptor == nullptr)
    {
        // TODO: some error handling?
        return;
    }

    _acceptor->async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
            if (!ec)
            {
                std::make_shared<ConnectionType>(std::move(socket))->accept();
            }

            accept();
        });
}

#endif  // SERVER_SERVER_H
