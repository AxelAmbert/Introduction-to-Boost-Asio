//
// Created by Axel Ambert on 23/10/2021.
//

//Source: https://www.boost.org/doc/libs/1_75_0/doc/html/boost_asio/tutorial/tutdaytime1/src.html

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: client <host>" << std::endl;
            return 1;
        }

        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        std::cout << argv[1] << std::endl;
        auto endpoints = tcp::endpoint( boost::asio::ip::address::from_string(argv[1]), 4242);
        tcp::socket socket(io_context);

        socket.connect( endpoints);
        for (;;)
        {
            boost::array<char, 128> buf;
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            if (error == boost::asio::error::eof)
                break; // Connection closed cleanly by peer.
            else if (error)
                throw boost::system::system_error(error); // Some other error.

            std::cout.write(buf.data(), len);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}