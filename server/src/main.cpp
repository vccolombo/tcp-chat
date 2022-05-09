#include <cstdint>
#include <iostream>
#include <memory>

#include "connectionchatfactory.h"
#include "server.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <port>" << std::endl;
        return 0;
    }

    try
    {
        uint16_t port = std::atoi(argv[1]);
        Server server(std::make_unique<ConnectionChatFactory>());
        server.open(port);
        server.start();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}