#include <iostream>
#include <cstdlib>
#include <pthread.h>

#include <zmq.hpp>
#include <string>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#define sleep(n)    Sleep(n)
#endif

using namespace std;

#define NUM_THREADS 5

void *listener(void *arg) {
  zmq::context_t context (1);
  zmq::socket_t socket (context, ZMQ_REQ);

  std::cout << "Connecting to hello world server…" << std::endl;
  socket.connect ("tcp://10.170.111.121:5555");
  // socket.connect ("tcp://localhost:5556");
  std::cout << "Connection Successful!" << std::endl;

  while(true){
    zmq::message_t request (5);

    char msg[100];

    // std::cout << "Enter the message" << std::endl;
    std::cin >> msg;

    memcpy (request.data (), msg, strlen(msg)+1 );
    socket.send (request);

    zmq::message_t reply;
    socket.recv (&reply);
  }
}

int main () {
  pthread_t threads;
  int rc;
  int i;
 
  cout << "creating listener thread" << endl;
  rc = pthread_create(&threads, NULL, listener, NULL);
    
  if (rc) {
    cout << "Error:unable to create listener thread," << rc << endl;
    exit(-1);
  }

  zmq::context_t context (1);
  zmq::socket_t socket (context, ZMQ_REP);
  socket.bind ("tcp://*:5555");

  while (true) {
    zmq::message_t request;

    //  Wait for next request from client
    socket.recv (&request);

    std::string res = std::string(static_cast<char*>(request.data()), request.size());

    std::cout << "[Yannick]:" << res << std::endl;
    //  Send reply back to client
    zmq::message_t reply (5);
    memcpy (reply.data (), "", 0);
    socket.send (reply);
  }
   
  pthread_exit(NULL);
}