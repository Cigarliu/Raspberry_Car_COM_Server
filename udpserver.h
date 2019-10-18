#ifndef UDPSERVER_H
#define UDPSERVER_H


#include <time.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>

namespace my_udp
{

class UdpServer
{
public:
  UdpServer();
  ~UdpServer();
  int UdpServerInit(const int port); // 创建一个用于监听的套接字，并返回套接字
  int ListenMessage(const int socket_id, char* data);  // 使用套接字进行监听
  int get_socket_id(){return socket_id_;}
  bool get_is_recv_message(){return is_recv_message_;}
  void set_is_recv_message(const bool status){is_recv_message_ = status;}
private:
  sockaddr_in source_addr_;  // 用于存储发送端的网络信息
  long com_counter_;
  int socket_id_;
  char source_ip_[INET_ADDRSTRLEN];
  bool is_recv_message_;
};
}



#endif // UDPSERVER_H
