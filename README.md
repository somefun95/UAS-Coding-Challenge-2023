This solution requires precompiling some C++ libraries. I've only tested it on Linux Ubuntu distro and can give instructions
on how to run the program.

Step 1: Check that boost library is installed. If not currently installed use the following instructions to install it"
sudo apt-get install -y libboost-all-dev

Step 2: Check that the Geographic library is installed. If not currently installed use the following instructions to install it:
sudo apt-get install -y geographiclib-tools
sudo apt-get install -y libgeographic-dev

Step 3: Compile and run the server program with the following commands:
g++ server.cpp -lboost_system -pthread -o server
./server

Step 4: Compile and run the client program with the following command:
g++ client.cpp -lboost_system -lGeographic -pthread -o client
./client