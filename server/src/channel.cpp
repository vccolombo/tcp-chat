#include "channel.h"

void Channel::enterChannel(ChannelObserver* const member, const std::string& nickname)
{
    _members.insert({member, nickname});

    for (const auto& observer : _members)
    {
        auto observer_ptr = observer.first;
        observer_ptr->onNewChannelMember(nickname);
    }
}

void Channel::exitChannel(ChannelObserver* const member)
{
    // TODO
}

void Channel::sendMessage(ChannelObserver* const member, const std::string& msg)
{
    auto nickname = _members.at(member);

    for (const auto& other_members : _members)
    {
        auto ptr = other_members.first;
        ptr->onMessage(nickname, msg);
    }
}
