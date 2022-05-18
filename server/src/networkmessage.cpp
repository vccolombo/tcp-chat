#include "networkmessage.h"

#include <cstdint>

NetworkMessage::NetworkMessage()
{
    buffer_ = new uint8_t[MAX_MSG_LENGTH];
}

NetworkMessage::~NetworkMessage()
{
    delete[] buffer_;
}

uint8_t* const NetworkMessage::header() const
{
    return buffer_;
}

uint8_t* const NetworkMessage::body() const
{
    return buffer_ + HEADER_LENGTH;
}

void NetworkMessage::parse_header()
{
    offset_ = 0;

    body_length_ = get<uint16_t>();
    protocol_version_ = get<uint16_t>();
    command_ = get<uint8_t>();
}

uint16_t NetworkMessage::msg_length() const
{
    return HEADER_LENGTH + body_length_;
}

uint16_t NetworkMessage::body_length() const
{
    return body_length_;
}

uint8_t NetworkMessage::command() const
{
    return command_;
}

std::string NetworkMessage::get_string()
{
    auto length = get<uint16_t>();
    auto str = std::string(buffer_ + offset_, buffer_ + offset_ + length);
    offset_ += length;
    return str;
}

void NetworkMessage::reset()
{
    offset_ = HEADER_LENGTH;
}

uint16_t NetworkMessage::update_length()
{
    body_length_ = offset_ - HEADER_LENGTH;
    set<uint16_t>(body_length_, 0);

    return body_length_;
}

void NetworkMessage::update_command(uint8_t command)
{
    command_ = command;
    set<uint8_t>(command, 4);
}

void NetworkMessage::add_string(const std::string& s)
{
    add<uint16_t>(s.length());
    for (const auto& c : s)
    {
        add<uint8_t>(c);
    }
}