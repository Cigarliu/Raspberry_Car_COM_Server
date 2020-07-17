#include "tcpserver.h"

using namespace my_tcp;

TcpServer::TcpServer()
{
  client_is_connect_ = false;
}

TcpServer::~TcpServer()
{
}

int TcpServer::TcpServerInit(const int port)
{
  sockaddr_in addr;
  int socket_id;
  socket_id = socket(AF_INET, SOCK_STREAM, 0);
  socket_id_ = socket_id;
  bzero(&addr, sizeof(addr));
  addr.sin_family      = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port        = htons(uint16_t(port));
  if(bind(socket_id, (struct sockaddr *)&addr, sizeof(addr)) == -1)
  {
    printf("Error To Bind Port \n");
    return -1;
  }
  return socket_id;
}



int TcpServer::ListenMessage(const int socket_id, char* data)
{
  int recv_socket_id;
  long n;
  if(listen(socket_id,10) != 0)
  {
      std::cerr << "listen fail" << std::endl;
      return 1; // num 1 is fail status
  }

  std::cerr << "listen ... " << std::endl;
  while(true)
  {
    if(!client_is_connect_)
    {
        if( (recv_socket_id = accept(socket_id, (struct sockaddr*)NULL, NULL)) == -1)
        {
           printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
           continue;
        }
        else
        {
            std::cerr << "device online " << std::endl;
        }
    }

    client_is_connect_  = true;  // 存在连接
    n = recv(recv_socket_id, data, 4096, 0);
    if(n <= 0)
    {
        client_is_connect_ = false;
        std::cerr << " \033[31m device offline ! \033[0m" << std::endl;
    }
    data[n] = '\0';
    printf("recv msg from client: %s\n", data);
    if(is_recv_command_from_udp_server_)
    {
      SendMessage(recv_socket_id, send_buffer_);
      memset(send_buffer_,0,sizeof (send_buffer_));
      is_recv_command_from_udp_server_ = false;
    }
  }
  close(socket_id);
}

void  TcpServer::SendMessage(const int socket_id, char *data)
{
  send(socket_id,data,128,0);
}
