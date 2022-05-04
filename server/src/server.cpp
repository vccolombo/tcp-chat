#include "server.h"

#include "connection.h"

void Server::start()
{
    io_context.run();
}

void Server::accept()
{
    acceptor.async_accept(
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
