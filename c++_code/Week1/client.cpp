//
//  Hello World client in C++
//  Connects REQ socket to tcp://localhost:5555
//  Sends "Hello" to server, expects "World" back
//
#include <zmq.hpp>
#include <string>
#include <iostream>

int main ()
{
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);

    std::cout << "Connecting to hello world server…" << std::endl;
    socket.connect ("tcp://localhost:5555");

    
    zmq::message_t request (5);

    char msg[100];

    std::cout << "Enter the message" << std::endl;
    std::cin >> msg;

    memcpy (request.data (), msg, strlen(msg)+1 );
    // std::cout << "Sending Hello " << request_nbr << "…" << std::endl;
    socket.send (request);

    //  Get the reply.
    // zmq::message_t reply;
    // socket.recv (&reply);
    // std::cout << "Received World " << request_nbr << std::endl;

    return 0;
}
