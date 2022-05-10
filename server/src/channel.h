#ifndef SERVER_CHANNEL_H
#define SERVER_CHANNEL_H

#include <string>
#include <unordered_map>

#include "channelsubject.h"

class Channel final : public ChannelSubject
{
   public:
    void enterChannel(std::shared_ptr<ChannelObserver> member, const std::string& nickname) override;
    void exitChannel(std::shared_ptr<ChannelObserver> member) override;

   private:
    std::unordered_map<std::shared_ptr<ChannelObserver>, std::string> _members;
};

#endif  // SERVER_CHANNEL_H
