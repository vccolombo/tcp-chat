#pragma once

#include <boost/asio.hpp>

#include "channelmanager.h"

using boost::asio::ip::tcp;

class Server
{
   public:
    Server(boost::asio::io_context& io_context, tcp::endpoint& endpoint);

    void accept();

   private:
    tcp::acceptor acceptor_;
    ChannelManager cm_;
};