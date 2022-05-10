#ifndef SERVER_CHANNELSUBJECT_H
#define SERVER_CHANNELSUBJECT_H

#include <memory>

#include "channelobserver.h"

class ChannelSubject
{
   public:
    virtual void enterChannel(std::shared_ptr<ChannelObserver> member, const std::string& nickname) = 0;
    virtual void exitChannel(std::shared_ptr<ChannelObserver> member) = 0;
};

#endif  // SERVER_CHANNELSUBJECT_H
