#include <iostream>
#include <boost/asio.hpp>

void runServer(int const &port) {
    try {
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));

        std::cout << "Server listening on port 12345..." << std::endl;

        while (true) {
            boost::asio::ip::tcp::socket socket(io_service);
            acceptor.accept(socket);

            std::string message = "Hello from the server!";
            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        }
    } catch (std::exception& e) {
        std::cerr << "Server Exception: " << e.what() << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: srvMsg <port>\n";
        return 1;
    }
    std::vector<std::string> args(argv, argv + argc);
    runServer(atoi(argv[1]));
    return 0;
}