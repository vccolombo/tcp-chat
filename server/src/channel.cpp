#include "channel.hpp"

void Channel::addToChannel(std::shared_ptr<Participant> newParticipant)
{
    members.push_front(newParticipant);

    for (const auto &member : members)
    {
        member->sendNewMemberJoined(newParticipant->getNickname());
    }
}
