// g++ .\test.cpp -I G:/cpp_no1/boost_1_73_0/boost_1_73_0/ -o test -lwsock32 -lws2_32
#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using namespace boost;
using namespace std;
using boost::asio::ip::tcp;

int main()
{
    try
    {
        asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 3200));
        boost::asio::ip::address robots[2];
        int connect = 0;
        boost::array<char, 128> buf;
        boost::system::error_code error;

            tcp::socket socket(io_service);
            acceptor.accept(socket);
        for (;;)
        {
            if(socket.is_open()) cout << "111" << endl;
            else cout<< "222" << endl;
            // if(socket.e)
            if(acceptor.is_open()) cout << "true" << endl;
            else{
                // acceptor
                cout << "false" << endl;
            }
            if (connect < 2)
            {
                // if(socket.remote_endpoint().data() == "ready"){}
                robots[connect++] = socket.remote_endpoint().address();
            }
            else
            {
                string msg = "are you ready?";
            }

            
            size_t len = socket.read_some(boost::asio::buffer(buf), error);
            std::cout.write(buf.data(), len);

            std::cout << socket.remote_endpoint().address() << std::endl;
            cout << socket.remote_endpoint().capacity() << endl;
            cout << socket.remote_endpoint().data() << endl;
            cout << socket.remote_endpoint().port() << endl;
            cout << socket.remote_endpoint().protocol().type() << endl;
            cout << socket.remote_endpoint().size() << endl;
            time_t now = time(0);
            std::string message = ctime(&now);

            system::error_code ignored_error;
            socket.write_some(asio::buffer(message), ignored_error);
            if (ignored_error)
            {
                std::cout << boost::system::system_error(ignored_error).what() << std::endl;
                cout << "333 " << ignored_error.value() << endl;
                cout << "555 " << ignored_error.message() << endl;

                // break;
                socket.close();
                acceptor.accept(socket);
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