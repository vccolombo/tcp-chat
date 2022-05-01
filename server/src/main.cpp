#include <cstdint>
#include <exception>
#include <iostream>

#include "server.hpp"

int main()
{
    try
    {
        uint16_t port = 1338;
        Server server(port);
        server.start();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}