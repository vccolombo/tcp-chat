#include "channel.h"

void Channel::addToChannel(std::shared_ptr<Participant> newParticipant)
{
    members.push_front(newParticipant);

    for (const auto &member : members)
    {
        member->sendNewMemberJoined(newParticipant->getNickname());
    }
}

void Channel::sendMessage(const std::string &from, const std::string &msg)
{
    for (const auto &member : members)
    {
        member->sendMessage(from, msg);
    }
}
