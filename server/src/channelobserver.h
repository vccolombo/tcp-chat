#ifndef SERVER_CHANNELOBSERVER_H
#define SERVER_CHANNELOBSERVER_H

#include <string>

class ChannelObserver
{
   public:
    virtual void onNewChannelMember(const std::string& nickname) = 0;
    virtual void onMessage(const std::string& from, const std::string& msg) = 0;
};

#endif  // SERVER_CHANNELOBSERVER_H
