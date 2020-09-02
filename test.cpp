// g++ .\test.cpp -I G:/cpp_no1/boost_1_73_0/boost_1_73_0/ -o test -lwsock32 -lws2_32
#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <random>

using namespace boost;
using namespace std;
using boost::asio::ip::tcp;
using std::default_random_engine;

int main()
{
    asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 3200));
    boost::asio::ip::address robots[2];
    boost::array<char, 128> buf[2];
    boost::system::error_code error;
    //initial
    int connect = 0;
    int first = -1;
    default_random_engine e;
    tcp::socket socket_pool[2] = {tcp::socket(io_service), tcp::socket(io_service)};
    system::error_code error_pool[2];
    try
    {
        for (;;)
        {
            if (connect < 2)
            {
                cout << connect << endl;
                acceptor.accept(socket_pool[connect]);
                robots[connect] = socket_pool[connect].remote_endpoint().address();
                connect++;
                continue;
            }

            first = e() % 2;
            socket_pool[first].write_some(asio::buffer("you first, are you ready?"), error_pool[first]);
            socket_pool[first].read_some(boost::asio::buffer(buf[first]), error);
            while ((string)(buf[first].data()) != "ready")
            {
                socket_pool[first].write_some(asio::buffer("you first, are you ready?"), error_pool[first]);
                socket_pool[first].read_some(boost::asio::buffer(buf[first]), error);
            }
            socket_pool[1 - first].write_some(asio::buffer("you second, are you ready?"), error_pool[1 - first]);
            socket_pool[1 - first].read_some(boost::asio::buffer(buf[1 - first]), error);
            while ((string)(buf[1 - first].data()) != "ready")
            {
                socket_pool[1 - first].write_some(asio::buffer("you second, are you ready?"), error_pool[1 - first]);
                socket_pool[1 - first].read_some(boost::asio::buffer(buf[1 - first]), error);
            }
            // game begin
            while (true)
            {
                cout << "game begin" << endl;
            }

            if (error_pool[first])
            {
                std::cout << boost::system::system_error(error_pool[first]).what() << std::endl;
                socket_pool[first].close();
                acceptor.accept(socket_pool[first]);
            }
            if (error_pool[1 - first])
            {
                std::cout << boost::system::system_error(error_pool[1 - first]).what() << std::endl;
                socket_pool[1 - first].close();
                acceptor.accept(socket_pool[1 - first]);
            }
        }
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        cout << "444" << endl;
    }
    return 0;
}

// socket_pool[first].write_some(asio::buffer("first"), error_pool[first]);
// socket_pool[1 - first].write_some(asio::buffer("second"), error_pool[1 - first]);

// std::this_thread::sleep_for(chrono::seconds(2));

// size_t len = socket.read_some(boost::asio::buffer(buf), error);
// std::cout.write(buf.data(), len);

// std::cout << socket.remote_endpoint().address() << std::endl;
// cout << socket.remote_endpoint().capacity() << endl;
// cout << socket.remote_endpoint().data() << endl;
// cout << socket.remote_endpoint().port() << endl;
// cout << socket.remote_endpoint().protocol().type() << endl;
// cout << socket.remote_endpoint().size() << endl;
// time_t now = time(0);
// std::string message = ctime(&now);

// cout << "333 " << ignored_error.value() << endl;
// cout << "555 " << ignored_error.message() << endl;