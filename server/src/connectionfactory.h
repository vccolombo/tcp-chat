#ifndef SERVER_CONNECTIONFACTORY_H
#define SERVER_CONNECTIONFACTORY_H

#include <memory>

#include "connection.h"

class ConnectionFactory
{
   public:
    virtual std::shared_ptr<Connection> createConnection(tcp::socket socket);

   private:
};

#endif  // SERVER_CONNECTIONFACTORY_H
