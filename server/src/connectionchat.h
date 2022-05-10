#ifndef SERVER_CONNECTIONCHAT_H
#define SERVER_CONNECTIONCHAT_H

#include <iostream>

#include "channel.h"
#include "channelobserver.h"
#include "connection.h"

class ConnectionChat final : public Connection, public ChannelObserver
{
   public:
    explicit ConnectionChat(tcp::socket socket) : Connection(std::move(socket)) {}

    void onAccept() override;
    void onData(uint8_t* data, uint16_t length) override;

    void onNewChannelMember(const std::string& nickname) override;
    void onMessage(const std::string& from, const std::string& msg) override;

   private:
    // TODO: remove this from here
    // my idea is to have the factory provide a ChannelManager
    // and then use this manager to get the correct channel
    static Channel _channel;
};

#endif  // SERVER_CONNECTIONCHAT_H
