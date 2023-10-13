#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>

using boost::asio::ip::udp;

enum
{
    max_length = 1024
};

void runClient(std::string &ip, std::string &port, char const *argv[])
{
    try
    {
        boost::asio::io_context io_context;

        udp::socket s(io_context, udp::endpoint(udp::v4(), 0));

        udp::resolver resolver(io_context);
        udp::endpoint endpoint =
            *resolver.resolve(udp::v4(), argv[1], argv[2]).begin();

        std::cout << "Trying to access server " << ip << ":" << port << std::endl;

        while (true)
        {
            std::cout << "Enter message: ";
            char request[max_length] = "";
            std::cin.getline(request, max_length - 1);
            size_t request_length = std::strlen(request);
            request[request_length] = '\0';
            s.send_to(boost::asio::buffer(request, request_length + 1), endpoint);
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Client Exception: " << e.what() << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: cltMsg <host> <port>\n";
        return 1;
    }
    std::vector<std::string> args(argv, argv + argc);
    runClient(args[1], args[2], argv);
    return 0;
}
