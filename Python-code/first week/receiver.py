#
#   Hello World client in Python
#   Connects REQ socket to tcp://localhost:5555
#   Sends "Hello" to server, expects "World" back
#

import zmq

context = zmq.Context()

#  Socket to talk to server
print("Connecting to hello world server...")
socket = context.socket(zmq.REQ)
socket.connect("tcp://10.170.110.134:5555")

#  Do 10 requests, waiting each time for a response
for request in range(20):
    print("Sending request %s ..." % request)
    hi = raw_input("please enter something: ")
    print("send "+ hi)
    socket.send(hi)
    #  Get the reply.
    message = socket.recv()
    print("Received reply %s [ %s ]" % (request, message))

