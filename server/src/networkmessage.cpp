#include "networkmessage.hpp"

#include "const.hpp"

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
