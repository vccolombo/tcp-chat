#pragma once

#include <memory>
#include <set>
#include <string>
#include <unordered_map>

#include "channelmember.h"

class Channel
{
   public:
    Channel(const std::string& name);

    void join(std::shared_ptr<ChannelMember> member_ptr, const std::string& nickname);
    void send_message(std::shared_ptr<ChannelMember> member_ptr, const std::string& text);

   private:
    std::string name_;
    std::unordered_map<std::shared_ptr<ChannelMember>, std::string> members_;
};