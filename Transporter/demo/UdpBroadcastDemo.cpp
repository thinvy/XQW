#include "../include/udpbd_transporter.hpp"
#include <iostream>
#include <unistd.h>

int main(int argc, char* argv[])
{
    std::string port_s = argv[1];
    int port = std::stoi(port_s);

    std::shared_ptr<transporter::Base> broadcast_tx;
    std::shared_ptr<transporter::Base> broadcast_rx;

    broadcast_tx = std::make_shared<transporter::UdpBroadcaster>("Transmit", port);
    broadcast_rx = std::make_shared<transporter::UdpBroadcaster>("Receive", port);

    if (broadcast_tx->open() != true) {
        std::cout << "open broadcast_tx error : " << broadcast_tx->error_message() << std::endl;
    }
    if (broadcast_rx->open() != true) {
        std::cout << "open broadcast_rx error : " << broadcast_rx->error_message() << std::endl;
    }

    std::string message = "Hello World";
 
    while (true)
    {
        const char *buffer_tx = message.c_str();
        int tx_result = broadcast_tx->write(buffer_tx, sizeof(buffer_tx));
        std::cout << "tx : " << buffer_tx << " =>> result : " << tx_result << std::endl;

        char buffer_rx[64];
        int rx_result = broadcast_rx->read(buffer_rx, sizeof(buffer_rx));
        std::cout << "rx : " << buffer_rx << " <<= result : " << rx_result << std::endl;

        usleep(1000000);
    }
    
}