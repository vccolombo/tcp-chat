#include "connectionchatfactory.h"

std::shared_ptr<Connection> ConnectionChatFactory::createConnection(tcp::socket socket)
{
    return std::make_shared<ConnectionChat>(std::move(socket));
}
