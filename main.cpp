#include <iostream>
#include "inc/network/Server.hpp"

int main() {
    Server server = Server();
    server.route();
    server.listen();
    return 0;
}
