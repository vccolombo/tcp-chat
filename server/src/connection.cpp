#include "connection.h"

#include <cstdio>
#include <iostream>

#include "networkmessage.h"

Connection::Connection(tcp::socket socket, ChannelManager &cm) : socket_(std::move(socket)), cm_(cm) {}

void Connection::accept()
{
    read_head();
}

void Connection::read_head()
{
    auto self(shared_from_this());
    async_read(socket_, boost::asio::buffer(msg_.header(), NetworkMessage::HEADER_LENGTH),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                msg_.parse_header();
                read_body();

                // go back to read next command
                read_head();
            }
            else
            {
                // cm_.leave(shared_from_this(), );
            }
        });
}

void Connection::read_body()
{
    auto self(shared_from_this());
    // TODO: there is something wronge here
    // changing this to async_read(socket_, ...) breaks things after the second read
    // I might be doing something wrong and async_read_some is covering for me...
    socket_.async_read_some(boost::asio::buffer(msg_.body(), msg_.body_length()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                parse_msg();
            }
            else
            {
            }
        });
}

void Connection::parse_msg()
{
    auto command = msg_.command();

    switch (command)
    {
        case 0x01:
            execute_command_join();
            break;
        case 0x02:
            execute_command_recv_msg();
            break;
    }
}

void Connection::execute_command_join()
{
    auto channel_name = msg_.get_string();
    auto nickname = msg_.get_string();
    auto channel = cm_.get(channel_name);
    if (channel != nullptr)
    {
        channel->join(shared_from_this(), nickname);
        channels_.insert(channel);
    }
    else
    {
        std::cout << "channel not found: " << channel_name << std::endl;
    }
}

void Connection::execute_command_recv_msg()
{
    // auto x = msg_.header();
    // for (int i = 0; i < msg_.body_length() + 5; i++)
    // {
    //     printf("%x ", x[i]);
    // }
    // printf("%\n");
    auto channel_name = msg_.get_string();
    auto text = msg_.get_string();
    auto channel = cm_.get(channel_name);
    if (channel != nullptr)
    {
        channel->send_message(shared_from_this(), text);
    }
    else
    {
        std::cout << "channel not found: " << channel_name << std::endl;
    }
}

void Connection::on_new_channel_member(const std::string &channel_name, const std::string &member_nickname)
{
    msg_.reset();
    msg_.update_command(0x04);
    msg_.add_string(channel_name);
    msg_.add_string(member_nickname);
    send();
}

void Connection::on_channel_message(
    const std::string &channel_name, const std::string &sender_nickname, const std::string &text)
{
    msg_.reset();
    msg_.update_command(0x03);
    msg_.add_string(channel_name);
    msg_.add_string(sender_nickname);
    msg_.add_string(text);
    send();
}

void Connection::send()
{
    auto self(shared_from_this());
    msg_.update_length();
    boost::asio::async_write(socket_, boost::asio::buffer(msg_.header(), msg_.msg_length()),
        [this, self](boost::system::error_code ec, std::size_t) {});
}
