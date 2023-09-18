// client.cpp
#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <GeographicLib/UTMUPS.hpp> 

using namespace boost::asio;
using namespace GeographicLib;

double calculate_distance(double x1, double y1, double x2, double y2) {
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int main() {
    io_service io_service;
    ip::tcp::socket socket(io_service);
    socket.connect(ip::tcp::endpoint(ip::address::from_string("127.0.0.1"), 12345));

    double previousX = 0, previousY = 0;
    double totalDistance = 0;
    int count = 0;
    size_t len;

    while (true) {
        boost::array<char, 128> buf;
        try{ 
            len = socket.read_some(buffer(buf));
        } catch (std::exception& e) {
            break;
        }
        if (len <= 0) break;

        std::string line(buf.data(), len);
        std::istringstream ss(line);
        double lat, lon;
        ss >> lat >> lon;

        double x, y;
        int zone;
        bool northp;
        UTMUPS::Forward(lat, lon, zone, northp, x, y);  // Convert to UTM
        
        if (count != 0) {
            double distance = calculate_distance(previousX, previousY, x, y);
            totalDistance += distance;
            std::cout << "Current speed: " << distance << " m/s" << std::endl;
        }

        previousX = x;
        previousY = y;
        count++;
    }

    std::cout << "\nAverage speed: " << totalDistance / count << " m/s" << std::endl;
    return 0;
}
