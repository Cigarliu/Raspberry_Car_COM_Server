#include <iostream>

#include "tcpserver.h"
#include "udpserver.h"

#include "controller.h"

int main()
{
  my_controller::Controller* server;
  server = new my_controller::Controller;
  server->Init(1234,8989);
  server->Start();
}
