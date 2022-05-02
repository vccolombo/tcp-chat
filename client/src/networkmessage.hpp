#ifndef SERVER_NETWORKMESSAGE_HPP
#define SERVER_NETWORKMESSAGE_HPP

#include <cstdint>
#include <cstring>
#include <string>

#include "const.hpp"

class NetworkMessage
{
   public:
    explicit NetworkMessage(uint16_t size);
    NetworkMessage();
    ~NetworkMessage();

    [[nodiscard]] uint8_t *getBuffer() const;

    uint8_t getByte();
    std::string getString();

    template <typename T>
    T get()
    {
        T v;
        memcpy(&v, buffer + position, sizeof(T));
        position += sizeof(T);
        return v;
    }

    void addString(const std::string &s);

    template <typename T>
    void add(T v)
    {
        memcpy(buffer + position, &v, sizeof(T));
        position += sizeof(T);
    }

    uint16_t getLength() const;

   private:
    uint16_t position = 0;
    uint8_t *buffer;
};

NetworkMessage::NetworkMessage(uint16_t size)
{
    buffer = new uint8_t[size];
    add<uint16_t>(0x0000);
    add<uint16_t>(0x0000);
}

NetworkMessage::NetworkMessage() : NetworkMessage(NETWORKMESSAGE_MAXSIZE) {}

NetworkMessage::~NetworkMessage()
{
    //    delete[] buffer;
}

uint8_t *NetworkMessage::getBuffer() const
{
    return buffer;
}

uint8_t NetworkMessage::getByte()
{
    return buffer[position++];
}

std::string NetworkMessage::getString()
{
    auto length = get<uint16_t>();
    auto str = std::string(buffer + position, buffer + position + length);
    position += length;
    return str;
}

uint16_t NetworkMessage::getLength() const
{
    return position;
}

void NetworkMessage::addString(const std::string &s)
{
    add<uint16_t>(s.length());
    for (const auto &c : s)
    {
        add<uint8_t>(c);
    }
}

#endif  // SERVER_NETWORKMESSAGE_HPP
