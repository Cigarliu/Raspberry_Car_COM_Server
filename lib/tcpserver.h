#ifndef TCPSERVER_H
#define TCPSERVER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<iostream>

namespace my_tcp
{

class TcpServer
{
public:
  TcpServer();
  ~TcpServer();
  int TcpServerInit(const int port); // 创建一个用于监听的套接字，并返回套接字
  int ListenMessage(const int socket_id, char* data);
  void SendMessage(const int socket_id, char* data);  // 发送消息给客户端
  int get_socket_id(){return socket_id_;}
  void set_udp_status(const bool is_recv){is_recv_command_from_udp_server_ = is_recv;}
  void set_send_buffer(char* data){memcpy(data,send_buffer_,128);}
  bool get_tcp_connect_status(){return client_is_connect_;}
private:
  bool client_is_connect_;
  sockaddr_in source_addr_;  // 用于存储发送端的网络信息
  long com_counter_;
  int socket_id_;
  char source_ip_[INET_ADDRSTRLEN];
  bool is_recv_command_from_udp_server_;
  char send_buffer_[128];
};
}



#endif // TCPSERVER_H
