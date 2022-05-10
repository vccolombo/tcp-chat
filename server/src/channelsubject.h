#ifndef SERVER_CHANNELSUBJECT_H
#define SERVER_CHANNELSUBJECT_H

#include "channelobserver.h"

class ChannelSubject
{
   public:
    virtual void enterChannel(ChannelObserver* member, const std::string& nickname) = 0;
    virtual void exitChannel(ChannelObserver* member) = 0;
    virtual void sendMessage(ChannelObserver* from, const std::string& msg) = 0;
};

#endif  // SERVER_CHANNELSUBJECT_H
