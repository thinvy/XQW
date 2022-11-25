#pragma once

#include "./transporter.hpp"

namespace transporter {

class UdpBroadcaster : public Base
{
//构造
public:
    UdpBroadcaster(std::string state, int port) : state_(state), port_(port) {}
    ~UdpBroadcaster() {close();}

// 继承功能
public:
    bool open() override;
    void close() override;
    int read(void * buffer, size_t len) override;
    int write(const void * buffer, size_t len) override;
    bool is_open() override {return is_open_;}
    std::string error_message() override {return error_message_;}
// 设备文件描述符
private:
    int socket_fd_;

// 设备状态
private:
    bool is_open_{false};
    std::string error_message_;
// 参数
private:
    std::string state_;
    int port_;
};


}