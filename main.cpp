#include <iostream>
#include "inc/network/Server.hpp"
#include "entities/Activity.h"
#include "Utils.hpp"
int main() {
    Server server = Server();
    server.route();
    server.listen();
    return 0;
}
