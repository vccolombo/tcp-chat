#include "connection.h"

void Connection::accept()
{
    onAccept();
    read();
}

void Connection::read()
{
    auto self(shared_from_this());

    auto data = new uint8_t[4096];
    // TODO: the message may not be read all in one call
    _socket.async_read_some(boost::asio::buffer(data, 4096),
        [this, self, data](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                onData(data, length);
            }

            delete[] data;
            read();
        });
}

void Connection::write(uint8_t* const data, uint16_t length)
{
    auto self(shared_from_this());

    boost::asio::async_write(_socket, boost::asio::buffer(data, length),
        [this, self, data](boost::system::error_code ec, std::size_t) { delete[] data; });
}
