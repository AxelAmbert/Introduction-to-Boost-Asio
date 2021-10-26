//
// Created by axela on 26/10/2021.
//

#ifndef UNTITLED_TCP_SERVER_HPP
#define UNTITLED_TCP_SERVER_HPP

#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <vector>
#include <time.h>
#include <algorithm>
#include <thread>
#include "tcp_connection.hpp"
#include "UsefulClass.hpp"




class tcp_server {
public:
    tcp_server(boost::asio::io_service &io_service);

private:
    void start_accept();


    /*
    * This function will call 100 times the modify_strings function.
    * Since the io_service is multi-threaded, it will happen concurrently.
    * Thus, accessing the same part of the memory at the same time.
    */
    void thread_attack(UsefulClass &usefulClass, boost::asio::io_service &io_service);


    void handle_accept(tcp_connection::pointer new_connection,
                       const boost::system::error_code &error);

    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::io_service &io_service_;
};


#endif //UNTITLED_TCP_SERVER_HPP
