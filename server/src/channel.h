#ifndef SERVER_CHANNEL_H
#define SERVER_CHANNEL_H

#include <string>
#include <unordered_map>

#include "channelsubject.h"

class Channel final : public ChannelSubject
{
   public:
    void enterChannel(ChannelObserver* member, const std::string& nickname) override;
    void exitChannel(ChannelObserver* member) override;

    void sendMessage(ChannelObserver* member, const std::string& msg) override;

   private:
    std::unordered_map<ChannelObserver*, std::string> _members;
};

#endif  // SERVER_CHANNEL_H
