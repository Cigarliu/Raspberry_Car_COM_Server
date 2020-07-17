#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <pthread.h>

#include "lib/udpserver.h"
#include "lib/tcpserver.h"

namespace my_controller
{

class Controller
{
public:
  Controller();
  ~Controller();
  void Init(int udp_listen_port, int tcp_listen_port);
  void Start();
  void ManageHandler();

  static void* TcpHandler(void* _this);
  static void* UdpHandler(void* _this);
  static void* TcpUdpStatusController(void* _this);
  static void* TcpCommandSend(void* _this);
  my_tcp::TcpServer* get_tcp_server(){return tcp_server_;}
  my_udp::UdpServer* get_udp_server(){return udp_server_;}
  char* get_udp_buffer(){return udp_buffer_;}
  char* get_tcp_buffer(){return tcp_buffer_;}
private:
  my_tcp::TcpServer* tcp_server_;
  my_udp::UdpServer* udp_server_;
  char udp_buffer_[128];
  char tcp_buffer_[128];
  bool is_recv_command_;
};

}


#endif // CONTROLLER_H
