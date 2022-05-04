#ifndef SERVER_CONNECTION_HPP
#define SERVER_CONNECTION_HPP

#include <boost/asio.hpp>
#include <memory>
#include <utility>

#include "channel.h"
#include "const.h"
#include "networkmessage.h"
#include "participant.h"

using boost::asio::ip::tcp;

class Connection : public std::enable_shared_from_this<Connection>
{
   public:
    explicit Connection(tcp::socket socket, std::shared_ptr<Channel> channel)
        : participant(std::make_shared<Participant>(std::move(socket))),
          channel(std::move(channel))
    {
    }

    void start();

   private:
    std::shared_ptr<Participant> participant;
    NetworkMessage msg;
    std::shared_ptr<Channel> channel;

    void read();

    void parsePacket(NetworkMessage msg, uint16_t length);
};

#endif  // SERVER_CONNECTION_HPP
