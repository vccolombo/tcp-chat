#ifndef SERVER_CONNECTIONCHAT_H
#define SERVER_CONNECTIONCHAT_H

#include <iostream>

#include "connection.h"

class ConnectionChat : public Connection
{
   public:
    explicit ConnectionChat(tcp::socket socket) : Connection(std::move(socket)) {}

    void onAccept() override;
    void onData(uint8_t* data, uint16_t length) override;
};

#endif  // SERVER_CONNECTIONCHAT_H
