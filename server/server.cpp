//
// Created by Axel Ambert on 26/10/2021.
//

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
#include "tcp_server.hpp"

int main() {
    constexpr bool multi_threading = true;

    srand(time(nullptr));
    try {
        boost::asio::io_service io_service;

        tcp_server server(io_service);
        if constexpr (multi_threading) {
            //TODO uncomment this line (Task 04)
            //enable_multi_threading(10, io_service);
        }
        io_service.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
