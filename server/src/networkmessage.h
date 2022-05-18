#pragma once

#include <cstdint>
#include <cstring>
#include <string>

#include "uncopyable.h"

class NetworkMessage final : private Uncopyable
{
   public:
    static constexpr uint8_t HEADER_LENGTH = 5;
    static constexpr uint16_t MAX_MSG_LENGTH = 4096;

    NetworkMessage();
    ~NetworkMessage();

    uint8_t *const header() const;
    uint8_t *const body() const;

    void parse_header();

    uint16_t msg_length() const;
    uint16_t body_length() const;
    uint8_t command() const;

    template <typename T>
    T get()
    {
        T v;
        memcpy(&v, buffer_ + offset_, sizeof(T));
        offset_ += sizeof(T);
        return v;
    }

    std::string get_string();

    void reset();
    uint16_t update_length();
    void update_command(uint8_t command);

    template <typename T>
    void add(T v)
    {
        set(v, offset_);
        offset_ += sizeof(T);
    }

    void add_string(const std::string &s);

   private:
    template <typename T>
    void set(T v, uint16_t offset)
    {
        memcpy(buffer_ + offset, &v, sizeof(T));
    }

    uint8_t *buffer_;
    uint16_t offset_;
    uint16_t body_length_;
    uint16_t protocol_version_;
    uint8_t command_;
};