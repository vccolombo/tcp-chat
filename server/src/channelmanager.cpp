#include "channelmanager.h"

#include <memory>

bool ChannelManager::create(const std::string& name)
{
    if (channels_.find(name) != channels_.end())
    {
        return false;
    }

    channels_.emplace(name, std::make_shared<Channel>(name));
    return true;
}

std::shared_ptr<Channel> ChannelManager::get(const std::string& name)
{
    if (channels_.find(name) == channels_.end())
    {
        return nullptr;
    }

    return channels_.at(name);
}