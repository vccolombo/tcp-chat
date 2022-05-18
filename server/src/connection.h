#pragma once

#include <boost/asio.hpp>
#include <memory>

#include "channelmanager.h"
#include "channelmember.h"
#include "networkmessage.h"

using boost::asio::ip::tcp;

class Connection final : public std::enable_shared_from_this<Connection>, public ChannelMember
{
   public:
    Connection(tcp::socket socket, ChannelManager& cm);

    void accept();

    void on_new_channel_member(const std::string& channel_name, const std::string& member_nickname) override;
    void on_channel_message(
        const std::string& channel_name, const std::string& sender_nickname, const std::string& text) override;

   private:
    void read_head();
    void read_body();
    void parse_msg();
    void execute_command_join();
    void execute_command_recv_msg();
    void send();

    tcp::socket socket_;
    ChannelManager& cm_;
    std::set<std::shared_ptr<Channel>> channels_;
    NetworkMessage msg_;
};