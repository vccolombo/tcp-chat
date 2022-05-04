#include <cstdint>
#include <exception>
#include <iostream>

#include "server.h"

int main(int argc, char *argv[])
{
    try
    {
        uint16_t port = std::atoi(argv[1]);
        Server server(port);
        server.start();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}