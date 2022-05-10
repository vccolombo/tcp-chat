#include "connectionchat.h"

Channel ConnectionChat::_channel;

void ConnectionChat::onAccept()
{
    std::cout << "onAccept" << std::endl;
}

void ConnectionChat::onData(uint8_t* const data, uint16_t length)
{
    std::cout << "onData: " << length << std::endl;

    if (length < 7)
    {
        return;
    }

    uint8_t command = data[4];

    if (command == 0x01)
    {
        uint16_t nickname_length;
        memcpy(&nickname_length, data + 5, sizeof(nickname_length));

        auto nickname = std::string(data + 7, data + 7 + nickname_length);

        _channel.enterChannel(std::shared_ptr<ChannelObserver>(this), nickname);
    }
}

void ConnectionChat::onNewChannelMember(const std::string& nickname)
{
    auto* msg = new uint8_t[512];

    msg[0] = 0;
    msg[1] = 0;
    msg[2] = 0;
    msg[3] = 0;
    msg[4] = 0x04;
    uint16_t nickname_length = nickname.length();
    memcpy(msg + 5, &nickname_length, sizeof(nickname_length));
    memcpy(msg + 7, nickname.c_str(), nickname_length);

    write(msg, 7 + nickname_length);
}
