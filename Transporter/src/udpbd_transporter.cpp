#include "../include/udpbd_transporter.hpp"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

namespace transporter {

bool UdpBroadcaster::open() {

    if(is_open_ == true) {
        return true;
    }

    socket_fd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd_ < 0 ) {
        error_message_ = "creat socket fail";
        return false;
    }

    // int flags = fcntl(socket_fd_, F_GETFL, 0); 
    // flags |= O_NONBLOCK;
    // int fcn = fcntl(socket_fd_, F_SETFL, flags);
    // if (fcn < 0) {
    //     error_message_ = "fcntl fail";
    //     return false;
    // }

    if (state_ == "Receive") {

        int on = 1;
	    int ret = setsockopt(socket_fd_, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	    if (ret < 0) {
		    error_message_ = "setsockopt fail";
		    return false;
	    }

        struct sockaddr_in  local_addr = {0};
        local_addr.sin_family  = AF_INET;
        local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        // local_addr.sin_addr.s_addr = inet_addr("192.168.0.100");
        local_addr.sin_port	= htons(port_);
        
        ret = bind(socket_fd_, (struct sockaddr*)&local_addr, sizeof(local_addr));
        if(ret < 0) {
            error_message_ = "bind fail";
            return false;
        }

        return true;
    }

    else if (state_ == "Transmit") {

        int on = 1;
	    int ret = setsockopt(socket_fd_, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
	    if (ret < 0) {
		    error_message_ = "setsockopt fail";
		    return false;
	    }
        ret = setsockopt(socket_fd_, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	    if (ret < 0) {
		    error_message_ = "setsockopt fail";
		    return false;
	    }

        struct sockaddr_in  local_addr = {0};
        local_addr.sin_family  = AF_INET;
        // local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        local_addr.sin_addr.s_addr = inet_addr("192.168.0.100");
        local_addr.sin_port	= htons(0);
        
        ret = bind(socket_fd_, (struct sockaddr*)&local_addr, sizeof(local_addr));
        if(ret < 0) {
            error_message_ = "bind fail";
            return false;
        }
        
    }
    else {
        error_message_ = "state set error";
        return false;
    }

    is_open_ = true;
    return true;
    
}


void UdpBroadcaster::close() {
    if (!is_open_) {
        return;
    }
    ::close(socket_fd_);
    is_open_ = false;
}


int UdpBroadcaster::read(void * buffer, size_t len) {
    
    struct sockaddr_in  recv_addr = {0};
    socklen_t recv_len;
    if (state_ == "Receive") {
        int rcv = recvfrom(socket_fd_, buffer, len, 0, (struct sockaddr *)&recv_addr, &recv_len);
        len = recv_len;
        return rcv;
    }
    else {
        error_message_ = "state error for receive : " + state_ ;
        return -1;
    }

}


int UdpBroadcaster::write(const void * buffer, size_t len) {
    
    struct sockaddr_in bro_addr = {0};
    bro_addr.sin_family = AF_INET;
    // bro_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    bro_addr.sin_addr.s_addr = bro_addr.sin_addr.s_addr = inet_addr("255.255.255.255");
    bro_addr.sin_port = htons(port_);

    if (state_ == "Transmit") {
        int send = sendto(socket_fd_, buffer, len, 0, (struct sockaddr *)&bro_addr, sizeof(bro_addr)); 
        return send;
    }
    else {
        error_message_ = "state error for receive : " + state_ ;
        return -1;
    }
}


}