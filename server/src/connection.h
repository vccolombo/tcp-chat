#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include <boost/asio.hpp>
#include <cstdint>
#include <memory>

using boost::asio::ip::tcp;

class Connection : public std::enable_shared_from_this<Connection>
{
   public:
    explicit Connection(tcp::socket socket) : _socket(std::move(socket)) {}

    void accept();
    void read();
    void write(uint8_t* data, uint16_t length);

    virtual void onAccept() {}
    virtual void onData(uint8_t* const data, uint16_t length) {}

   private:
    tcp::socket _socket;
};

#endif  // SERVER_CONNECTION_H
