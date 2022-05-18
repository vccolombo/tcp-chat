#include "server.h"

#include <memory>

#include "connection.h"

Server::Server(boost::asio::io_context& io_context, tcp::endpoint& endpoint) : acceptor_(io_context, endpoint)
{
    cm_.create("default");
}

void Server::accept()
{
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
            if (!ec)
            {
                std::make_shared<Connection>(std::move(socket), cm_)->accept();
            }

            accept();
        });
}