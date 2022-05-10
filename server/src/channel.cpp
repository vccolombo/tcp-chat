#include "channel.h"

void Channel::enterChannel(std::shared_ptr<ChannelObserver> member, const std::string& nickname)
{
    _members.insert({member, nickname});

    for (const auto& observer : _members)
    {
        auto observer_ptr = observer.first;
        observer_ptr->onNewChannelMember(nickname);
    }
}

void Channel::exitChannel(std::shared_ptr<ChannelObserver> member)
{
    // TODO
}
