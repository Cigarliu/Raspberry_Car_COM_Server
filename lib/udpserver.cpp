#include "udpserver.h"

using namespace my_udp;

UdpServer::UdpServer()
{
  com_counter_ = 0;
}

UdpServer::~UdpServer()
{

}


int UdpServer::UdpServerInit(const int port)
{
  sockaddr_in addr;
  int socket_id;
  socket_id = socket(AF_INET, SOCK_DGRAM, 0);
  socket_id_ = socket_id;
  bzero(&addr, sizeof(addr));
  addr.sin_family      = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port        = htons(uint16_t(port));
  bind(socket_id, (struct sockaddr *)&addr, sizeof(addr));
  return socket_id;
}


int UdpServer::ListenMessage(const int socket_id, char* data)
{
  char source_ip[INET_ADDRSTRLEN];
  int data_length;
  socklen_t sockadd_length;
  sockadd_length = sizeof(sockaddr_in);
  timeval tv = {2,0};
  setsockopt(socket_id,SOL_SOCKET,SO_RCVTIMEO, (char*)&tv, sizeof(timeval));
  data_length = recvfrom(socket_id, data, 30000, MSG_WAITALL, (struct sockaddr*) &source_addr_,&sockadd_length);
  // std::cout << "\033[31m 收到无效数据 ！\033[0m" << std::endl;
  if(data_length  < 1)
  {
    com_counter_++;
    if(com_counter_ > 3)
    {
      std::cout << "\033[31m通信中断或不存在连接 \033[35m" << com_counter_ - 2 << "\033[0m " << std::endl;
    }
    return data_length;  // 数据不正确， 直接返回
  }
  com_counter_ = 0;
  in_addr in  = source_addr_.sin_addr;
  inet_ntop(AF_INET,&in, source_ip, sizeof(source_ip));
  memcpy(source_ip_, source_ip, INET_ADDRSTRLEN);  // 得到发送端的Ｉp
  std::cout << "\033[34m 收到设备消息 IP: \033[36m" << source_ip_ << "\033[0m" << std::endl;
  is_recv_message_ = true;  //　收到消息　标志位
  return data_length;
}
