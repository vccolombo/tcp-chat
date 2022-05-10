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

    // TODO: move this to a better place, like a parseMessage method
    // TODO: probably better as a switch
    if (command == 0x01)
    {
        uint16_t nickname_length;
        memcpy(&nickname_length, data + 5, sizeof(nickname_length));

        auto nickname = std::string(data + 7, data + 7 + nickname_length);

        _channel.enterChannel(this, nickname);
    }
    else if (command == 0x02)
    {
        uint16_t msg_length;
        memcpy(&msg_length, data + 5, sizeof(msg_length));
        auto msg = std::string(data + 7, data + 7 + msg_length);

        _channel.sendMessage(this, msg);
    }
}

void ConnectionChat::onNewChannelMember(const std::string& nickname)
{
    // TODO: create a message class
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

void ConnectionChat::onMessage(const std::string& from, const std::string& msg)
{
    auto* data = new uint8_t[512];

    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
    data[4] = 0x03;
    uint16_t nickname_length = from.length();
    memcpy(data + 5, &nickname_length, sizeof(nickname_length));
    memcpy(data + 7, from.c_str(), nickname_length);

    uint16_t msg_length = msg.length();
    memcpy(data + 7 + nickname_length, &msg_length, sizeof(msg_length));
    memcpy(data + 9 + nickname_length, msg.c_str(), msg_length);

    write(data, 9 + nickname_length + msg_length);
}
