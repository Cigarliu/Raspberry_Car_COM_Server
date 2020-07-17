#include <iostream>

#include "lib/tcpserver.h"
#include "lib/udpserver.h"

#include "lib/controller.h"

int main()
{
  my_controller::Controller* server;
  server = new my_controller::Controller();
  server->Init(1234,8989);
  server->Start();
}
