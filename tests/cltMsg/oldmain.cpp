#include <iostream>
#include <boost/asio.hpp>

void runClient(std::string &ip, std::string &port) {
    try {
        std::cout << "Trying to access server " << ip << ":" << port << std::endl;
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::resolver resolver(io_service);
        boost::asio::ip::tcp::resolver::query query(ip, port);
        boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        boost::asio::ip::tcp::socket socket(io_service);
        
        boost::asio::connect(socket, endpoint_iterator);

        boost::asio::streambuf response;
        boost::asio::read(socket, response);

        std::istream response_stream(&response);
        std::string message;
        std::getline(response_stream, message);

        std::cout << "Received message from server: " << message << std::endl;
    } catch (std::exception& e) {
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
    runClient(args[1], args[2]);
    return 0;
}
