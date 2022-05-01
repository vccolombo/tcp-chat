#include "participant.hpp"

#include <memory>
#include <utility>

void Participant::setNickname(std::string newNickname)
{
    this->nickname = std::move(newNickname);
}

const std::string &Participant::getNickname() const
{
    return nickname;
}

void Participant::sendNewMemberJoined(const std::string &newMemberNickname)
{
    std::cout << nickname << ": sending new member " << newMemberNickname
              << " joined\n";

    NetworkMessage msg;
    msg.add<uint8_t>(0x04);
    msg.addString(newMemberNickname);
    innerSend(msg);
}

void Participant::sendMessage(const std::string &s)
{
    std::cout << nickname << ": sending msg '" << s << "'\n";

    NetworkMessage msg;
    msg.add<uint8_t>(0x03);
    msg.addString(s);
    innerSend(msg);
}

void Participant::innerSend(NetworkMessage &msg)
{
    auto self(shared_from_this());
    boost::asio::async_write(
        socket, boost::asio::buffer(msg.getBuffer(), msg.getLength()),
        [this, self](boost::system::error_code ec, std::size_t)
        {
            if (!ec)
            {
            }
        });
}
