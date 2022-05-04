#ifndef SERVER_CHANNEL_HPP
#define SERVER_CHANNEL_HPP

#include <list>
#include <memory>
#include <string>

#include "participant.h"

class Channel
{
   public:
    Channel() = default;

    void addToChannel(std::shared_ptr<Participant> newParticipant);
    void sendMessage(const std::string &from, const std::string &msg);

   private:
    std::list<std::shared_ptr<Participant>> members;
};

#endif  // SERVER_CHANNEL_HPP