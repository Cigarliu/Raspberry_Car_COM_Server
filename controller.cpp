#include "controller.h"

using namespace my_controller;

Controller::Controller()
{

}

void Controller::Init(int udp_listen_port, int tcp_listen_port)
{
  udp_server_ = new my_udp::UdpServer();
  tcp_server_ = new my_tcp::TcpServer();
  udp_server_->UdpServerInit(udp_listen_port);
  tcp_server_->TcpServerInit(tcp_listen_port);
}

void* Controller::TcpHandler(void *_this)
{
std::cout << "Thread TcpHandler ok \n" << std::endl;
  Controller* controller =  static_cast<Controller*>(_this);
  controller->get_tcp_server()->ListenMessage(controller->get_tcp_server()->get_socket_id(),controller->udp_buffer_);
}

void* Controller::UdpHandler(void *_this)
{
  std::cout << "Thread UdpHandler ok \n" << std::endl;
  Controller* controller =  static_cast<Controller*>(_this);
  char* udp_buffer;
  udp_buffer = controller->get_udp_buffer();
  int socket_id;
  socket_id =  controller->get_udp_server()->get_socket_id();
  while (true)
  {
    controller->get_udp_server()->ListenMessage(socket_id,udp_buffer);
  }

}




void* Controller::TcpUdpStatusController(void* _this)
{
  std::cout << "Thread TcpUdpStatusController ok \n" << std::endl;
  Controller* controller = static_cast<Controller*>(_this);
  int counter_1 = 0;
  int counter_2 = 0;
  while(true)
  {
    if(controller->get_udp_server()->get_is_recv_message() == true)
    {
      controller->get_tcp_server()->set_udp_status(true);
      std::cout << " 收到UDP请求消息，交给TCP线程处理" << std::endl;
      controller->get_udp_server()->set_is_recv_message(false);
    }
    if(!controller->get_tcp_server()->get_tcp_connect_status() )
    {
      counter_1++;
      if((counter_2 + 10000) < counter_1)
      {
        std::cout << "不存在TCP客户端请求 " << counter_1<< std::endl;
        counter_2 = counter_2 + 10000;
      }
    }
    else
    {
      std::cout << " 已建立和设备的TCP连接 " << std::endl;
    }

    usleep(100);
  }
}


void Controller::Start()
{
  pthread_t thread_udp_handler;
  pthread_t thread_tcp_handler;
  pthread_t thread_tcp_udp_status_controller;

  if(pthread_create(&thread_udp_handler, NULL, UdpHandler, (void*)this))
  {
    std::cout << "Create pthread UdpHandler fail " << std::endl;
  }

  if(pthread_create(&thread_tcp_handler, NULL, TcpHandler, (void*)this))
  {
    std::cout << "Create pthread UdpHandler fail " << std::endl;
  }

  if(pthread_create(&thread_tcp_udp_status_controller, NULL, TcpUdpStatusController, (void*)this))
  {
    std::cout << "Create pthread UdpHandler fail " << std::endl;
  }

  pthread_join(thread_udp_handler, NULL); // joints all the threads.
  pthread_join(thread_tcp_handler, NULL);
  pthread_join(thread_tcp_udp_status_controller, NULL);

}