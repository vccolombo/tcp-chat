#ifndef SERVER_NETWORKMESSAGE_HPP
#define SERVER_NETWORKMESSAGE_HPP

#include <cstdint>
#include <cstring>
#include <string>

class NetworkMessage
{
   public:
    explicit NetworkMessage(uint16_t size);
    NetworkMessage();
    ~NetworkMessage();

    [[nodiscard]] uint8_t *getBuffer() const;

    uint8_t getByte();
    std::string getString();

    template <typename T>
    T get()
    {
        T v;
        memcpy(&v, buffer + position, sizeof(T));
        position += sizeof(T);
        return v;
    }

    void addString(const std::string &s);

    template <typename T>
    void add(T v)
    {
        set(v, position);
        position += sizeof(T);
    }

    uint16_t getLength() const;
    void updateBodyLength();

   private:
    template <typename T>
    void set(T v, uint16_t offset)
    {
        memcpy(buffer + offset, &v, sizeof(T));
    }

    uint16_t position = 0;
    uint8_t *buffer;
};

#endif  // SERVER_NETWORKMESSAGE_HPP
