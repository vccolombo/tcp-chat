#include "connectionfactory.h"

std::shared_ptr<Connection> ConnectionFactory::createConnection(tcp::socket socket)
{
    return std::make_shared<Connection>(std::move(socket));
}