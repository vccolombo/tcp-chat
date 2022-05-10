#include "server.h"

void Server::open(uint16_t port)
{
    _acceptor = std::make_unique<tcp::acceptor>(
        _io_context, tcp::endpoint(tcp::v4(), port));
    accept();
}

void Server::start()
{
    _io_context.run();
}

void Server::accept()
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
                _connection_factory->createConnection(std::move(socket))
                    ->accept();
            }

            accept();
        });
}