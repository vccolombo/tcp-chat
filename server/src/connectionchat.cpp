#include "connectionchat.h"

void ConnectionChat::onAccept()
{
    std::cout << "onAccept" << std::endl;
}

void ConnectionChat::onData(uint8_t* const data, uint16_t length)
{
    std::cout << "onData: " << length << std::endl;
}
