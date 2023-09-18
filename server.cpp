// server.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/asio.hpp>

using namespace boost::asio;

int main() {
    io_service io_service;
    ip::tcp::acceptor acceptor(io_service, ip::tcp::endpoint(ip::tcp::v4(), 12345));
    
    std::cout << "Server started. Waiting for connection...\n";
    ip::tcp::socket socket(io_service);
    acceptor.accept(socket);
    std::cout << "Client connected.\n";

    std::ifstream file("missionwaypoints.txt");
    if (!file) {
        std::cerr << "Error opening the file.\n";
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        socket.write_some(buffer(line + "\n"));
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    file.close();
    socket.close();
    return 0;
}
