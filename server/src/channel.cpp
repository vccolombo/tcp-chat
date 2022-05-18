#include "channel.h"

Channel::Channel(const std::string& name) : name_(std::move(name)) {}

void Channel::join(std::shared_ptr<ChannelMember> member_ptr, const std::string& nickname)
{
    members_.insert({member_ptr, nickname});

    for (const auto& member : members_)
    {
        auto member_ptr = member.first;
        member_ptr->on_new_channel_member(name_, nickname);
    }
}

void Channel::send_message(std::shared_ptr<ChannelMember> member_ptr, const std::string& text)
{
    auto nickname = members_.at(member_ptr);

    for (const auto& member : members_)
    {
        auto member_ptr = member.first;
        member_ptr->on_channel_message(name_, nickname, text);
    }
}