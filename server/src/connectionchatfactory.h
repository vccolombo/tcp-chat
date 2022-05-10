#ifndef SERVER_CONNECTIONCHATFACTORY_H
#define SERVER_CONNECTIONCHATFACTORY_H

#include <memory>

#include "connectionchat.h"
#include "connectionfactory.h"

class ConnectionChatFactory final : public ConnectionFactory
{
   public:
    std::shared_ptr<Connection> createConnection(tcp::socket socket) override;

   private:
};

#endif  // SERVER_CONNECTIONCHATFACTORY_H
