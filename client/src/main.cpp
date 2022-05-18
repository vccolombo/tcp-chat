#include <boost/asio.hpp>
#include <deque>
#include <iostream>
#include <string>
#include <thread>

#include "const.hpp"
#include "networkmessage.hpp"

using boost::asio::ip::tcp;

class Protocol
{
   public:
    static void parsePacket(NetworkMessage msg);
};

void Protocol::parsePacket(NetworkMessage msg)
{
    std::string channel, nickname, text;

    auto command = msg.get<uint8_t>();
    switch (command)
    {
        case 0x03:
            channel = msg.getString();
            nickname = msg.getString();
            text = msg.getString();
            std::cout << channel << "> " << nickname << ": " << text
                      << std::endl;
            break;
        case 0x04:
            channel = msg.getString();
            nickname = msg.getString();
            std::cout << channel << "> " << nickname << " has entered the chat"
                      << std::endl;
            break;

        default:
            break;
    }
}
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

    void loopRead();
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
    loopRead();
}

void Client::send(const NetworkMessage &msg)
{
    socket.send(boost::asio::buffer(msg.getBuffer(), msg.getLength()));
}

void Client::loopRead()
{
    NetworkMessage msg;
    while (true)
    {
        socket.read_some(
            boost::asio::buffer(msg.getBuffer(), NETWORKMESSAGE_MAXSIZE));
        Protocol::parsePacket(msg);
    }
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
        msg.addString("default");
        msg.addString(nickname);
        msg.updateBodyLength();
        client.send(msg);

        std::string s;
        while (std::getline(std::cin, s))
        {
            NetworkMessage msg;
            msg.add<uint8_t>(0x02);
            msg.addString("default");
            msg.addString(s);
            msg.updateBodyLength();
            client.send(msg);
        }

        t.join();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}