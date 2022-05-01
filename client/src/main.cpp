#include <boost/asio.hpp>
#include <deque>
#include <iostream>
#include <string>
#include <thread>

#include "const.hpp"
#include "networkmessage.hpp"

using boost::asio::ip::tcp;

class Client
{
  public:
    Client();

    void connect(const std::string &host, const std::string &port);
    void start();

    void send(const NetworkMessage &msg);

  private:
    boost::asio::io_context io_context;
    tcp::resolver resolver;
    tcp::socket socket;
};

Client::Client() : resolver(io_context), socket(io_context) {}

void Client::connect(const std::string &host, const std::string &port)
{
    auto endpoints = resolver.resolve(host, port);
    boost::asio::connect(socket, endpoints);
}

void Client::start()
{
    io_context.run();

    char data[NETWORKMESSAGE_MAXSIZE];
    while (true)
    {
        socket.read_some(boost::asio::buffer(data, NETWORKMESSAGE_MAXSIZE));
        std::cout << "read\n";
    }
}

void Client::send(const NetworkMessage &msg)
{
    socket.send(boost::asio::buffer(msg.getBuffer(), msg.getLength()));
}

int main(int argc, char *argv[])
{
    try
    {
        Client client;
        client.connect(argv[1], argv[2]);

        std::thread t([&client]() { client.start(); });

        std::string nickname;
        std::cout << "nickname: ";
        std::cin >> nickname;

        NetworkMessage msg;
        msg.add<uint8_t>(0x01);
        msg.addString(nickname);
        client.send(msg);

        // char line[NETWORKMESSAGE_MAXSIZE + 2];
        // while (std::cin.getline(line, NETWORKMESSAGE_MAXSIZE + 1))
        // {
        //     // NetworkMessage msg;
        //     // msg.body_length(std::strlen(line));
        //     // std::memcpy(msg.body(), line, msg.body_length());
        //     // msg.encode_header();
        //     // c.write(msg);
        // }

        t.join();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}