/* 
 * [2022] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

#include <ethernet-connector.h>
#include <iostream>

const std::string EthConn::LOCAL_HOST = "127.0.0.1";

EthConn::EthConn(const std::string& ip_addr, int port_num)
:
ip(ip_addr),
port(port_num)
{

}

EthConn::EthConn(int port_num)
:
ip(EthConn::LOCAL_HOST),
port(port_num)
{

}

// Exercise 1: implement the overloaded stream operator and the print() method for EthConn