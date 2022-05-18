#pragma once

#include <string>

class ChannelMember
{
   public:
    virtual void on_new_channel_member(const std::string &channel_name, const std::string &member_nickname) = 0;
    virtual void on_channel_message(
        const std::string &channel_name, const std::string &sender_nickname, const std::string &text) = 0;
};