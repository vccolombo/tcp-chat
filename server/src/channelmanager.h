#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "channel.h"
#include "channelmember.h"

class ChannelManager
{
   public:
    bool create(const std::string& name);
    std::shared_ptr<Channel> get(const std::string& name);

   private:
    std::unordered_map<std::string, std::shared_ptr<Channel>> channels_;
};