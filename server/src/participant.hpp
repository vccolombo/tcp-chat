#ifndef SERVER_PARTICIPANT_HPP
#define SERVER_PARTICIPANT_HPP

#include "networkmessage.hpp"
#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

class Participant : public std::enable_shared_from_this<Participant>
{
  public:
    tcp::socket socket;

    explicit Participant(tcp::socket socket) : socket(std::move(socket)) {}

    void setNickname(std::string newNickname);

    [[nodiscard]] const std::string &getNickname() const;

    void sendNewMemberJoined(const std::string &newMemberNickname);
    void sendMessage(const std::string &from, const std::string &msg);

  private:
    std::string nickname;

    void innerSend(NetworkMessage &msg);
};

#endif // SERVER_PARTICIPANT_HPP
