#include "server.h"

#include <memory>

#include "connection.h"

void Server::open(uint16_t port)
{
    acceptor = std::make_unique<tcp::acceptor>(
        io_context, tcp::endpoint(tcp::v4(), port));
    accept();
}

void Server::start()
{
    io_context.run();
}

void Server::accept()
{
    if (acceptor == nullptr)
    {
        // TODO: some error handling?
        return;
    }

    acceptor->async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
            if (!ec)
            {
                std::make_shared<Connection>(std::move(socket), channel)
                    ->start();
            }

            accept();
        });
}
