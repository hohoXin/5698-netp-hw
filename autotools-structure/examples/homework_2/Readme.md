# HW2 Readme

by: Xinzhi Zhang

## compile the proxy.cpp

☐ You need to unzip the `homework_2_XinzhiZhang.tar.gz` file

☐ Compile the `proxy.cpp` file using autotool provided by professor.

## run the proxy_server

You can check if the program works proper by following these steps:

Open 3 terminals and do the following in the same order.

☐ Open a netcat UDP server on one of the terminals using:

   `nc -lu -p <udp_port_number>`

   The default UDP port_number of the proxy is 55556

☐ Open the `proxy_server` executable you just compiled on the other terminal. 

   The command is like `./proxy_server <tcp_port_number> <udp_port_number>`

☐ On the third terminal, open a netcat TCP client by using:

   `nc 127.0.0.1 <tcp_port_number>`

   The default IP is 127.0.0.1 and the default port number is 55557

☐ Now type something in the TCP client window. The proxy should receive the data and pass it on to the UDP server and print it out in the UDP server window.