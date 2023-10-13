#include <iostream>
#include <boost/asio.hpp>

void runServer() {
    try {
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 12345));

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

int main() {
    runServer();
    return 0;
}