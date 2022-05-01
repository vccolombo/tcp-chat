#include "connection.hpp"

#include <boost/asio.hpp>
#include <iostream>

#include "const.hpp"

void Connection::start()
{
    read();
}

void Connection::read()
{
    auto self(shared_from_this());

    // TODO: the message may not be read all in one call
    participant->socket.async_read_some(
        boost::asio::buffer(msg.getBuffer(), NETWORKMESSAGE_MAXSIZE),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                parsePacket(msg, length);
            }
        });
}

void Connection::parsePacket(NetworkMessage &msg, uint16_t length)
{
    std::cout << "Received new packet" << std::endl;
    auto command = msg.getByte();

    switch (command)
    {
    case 0x01:
        participant->setNickname(msg.getString());
        channel->addToChannel(participant);
        break;
    default:
        std::cout << "Unknown command!\n";
    }
}

void Connection::write(std::size_t length)
{
    auto self(shared_from_this());
    boost::asio::async_write(
        participant->socket, boost::asio::buffer(msg.getBuffer(), length),
        [this, self](boost::system::error_code ec, std::size_t)
        {
            if (!ec)
            {
                read();
            }
        });
}