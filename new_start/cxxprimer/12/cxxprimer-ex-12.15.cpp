#include <iostream>
#include <memory>
#include <string>

using std::string;

struct Connection {
    string ip;
    int port;
    Connection(string& _ip, int _port):
        ip(_ip), port(_port) { }
};

struct Destination {
    string ip;
    int port;
    Destination(const string& _ip, int _port):
        ip(_ip), port(_port) { }
};

Connection connect(Destination* pDest) {
    std::shared_ptr<Connection>
        pConn = std::make_shared<Connection>(pDest -> ip, pDest -> port);
    std::cout << "creating connection: ("
        << pConn.use_count() << ")" << std::endl;
    return *pConn;
}

void disconnect(Connection Conn) {
    std::cout << "connection close: "
        << Conn.ip << ":"
        << Conn.port << std::endl;
}


void f(Destination& d) {
    Connection conn = connect(&d);
    std::shared_ptr<Connection>
        p(&conn, [](Connection* pConn){ disconnect(*pConn); });
    std::cout << "connect now: "
        << p.use_count() << std::endl;
}

// test
int main() {
    Destination dst("192.168.1.1", 1080);
    f(dst);
    return 0;
}
