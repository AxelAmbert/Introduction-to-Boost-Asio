//
// Created by Axel Ambert on 23/10/2021.
//

//Source: https://www.boost.org/doc/libs/1_35_0/doc/html/boost_asio/tutorial/tutdaytime3/src.html

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
#include <functional>
#include <thread>

using boost::asio::ip::tcp;

std::vector<std::string> useless_strings_;

void init_strings() {
    useless_strings_.reserve(10000);
    for (int i = 0; i < 10000; i++) {
        std::string m;

        m.reserve(1000);
        for (int t = 0; t < 1000; t++) {
            m.push_back((char)(65 + rand() % 26));
        }
        useless_strings_.push_back(m);
    }
}

template<typename T>
T clamp(const T& val, const T& min, const T& max) {
    if (val > max)
        return max;
    else if (val < min) {
        return min;
    }
    return val;
}

void modify_a_string(std::string &str) {

    if (str.length() > 10) {
        str = str.substr(0, str.length() - 10);
    }
    for (char & i : str) {
        char r = (char)(rand() % 52);

        r = r < 26 ? r : -(r - (char)26);
        i += r;
        i = clamp<char>(i, 65, 90);
    }
    for (int i = 0; i < 10; i++) {
        str.push_back(rand() % 26 + 65);
    }
}

void modify_strings() {
    std::cout << "go " << std::endl;
    std::for_each(useless_strings_.begin(), useless_strings_.end(), modify_a_string);
    std::cout << "end " << std::endl;
}

void thread_attack(boost::asio::io_service &io_service) {
    for (int i = 0; i < 100; i++) {
        io_service.post(modify_strings);
    }
}

std::string make_daytime_string()
{
    using namespace std;
    time_t now = time(0);
    return ctime(&now);
}

class tcp_connection
        : public boost::enable_shared_from_this<tcp_connection>
{
public:
    typedef boost::shared_ptr<tcp_connection> pointer;

    static pointer create(boost::asio::io_service& io_service)
    {
        return pointer(new tcp_connection(io_service));
    }

    tcp::socket& socket()
    {
        return socket_;
    }

    void start()
    {
        message_ = make_daytime_string();

        boost::asio::async_write(socket_, boost::asio::buffer(message_),
                                 boost::bind(&tcp_connection::handle_write, shared_from_this(),
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
    }

private:
    tcp_connection(boost::asio::io_service& io_service)
            : socket_(io_service)
    {
    }

    void handle_write(const boost::system::error_code& code,
                      size_t byte_read)
    {
    }

    tcp::socket socket_;
    std::string message_;
};

class tcp_server
{
public:
    tcp_server(boost::asio::io_service& io_service)
            : acceptor_(io_service, tcp::endpoint(tcp::v4(), 4242)),
            io_service_(io_service)
    {
        start_accept();
    }

private:
    void start_accept()
    {
        tcp_connection::pointer new_connection =
                tcp_connection::create(io_service_);

        acceptor_.async_accept(new_connection->socket(),
                               boost::bind(&tcp_server::handle_accept, this, new_connection,
                                           boost::asio::placeholders::error));
    }

    void handle_accept(tcp_connection::pointer new_connection,
                       const boost::system::error_code& error)
    {
        if (!error)
        {
            new_connection->start();
            thread_attack(io_service_);
            start_accept();

        }
    }

    tcp::acceptor acceptor_;
    boost::asio::io_service &io_service_;
};

void enable_multi_threading(int nb_of_thread, boost::asio::io_service &io_service) {
    for (int i = 0; i < nb_of_thread; ++i) {
        std::thread thread([&] () {
            io_service.run();
        });
        thread.detach();
    }
}

int main()
{
    constexpr bool multi_threading = true;

    init_strings();
    srand(time(nullptr));
    try
    {
        boost::asio::io_service io_service;
        tcp_server server(io_service);
        if constexpr (multi_threading) {
            enable_multi_threading(10, io_service);
        }

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}