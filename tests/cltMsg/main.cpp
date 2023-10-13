#include <iostream>
#include <boost/asio.hpp>

void runClient() {
    try {
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::resolver resolver(io_service);
        boost::asio::ip::tcp::resolver::query query("localhost", "12345");
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

int main() {
    runClient();
    return 0;
}
