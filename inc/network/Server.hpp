#pragma once

#include "repositories/LocalDataRepository.hpp"
#include "httplib/httplib.h"

class Server {
private:
    httplib::Server* m_server;
    LocalDataRepository* m_dataSource;
    std::string m_host;
    int m_port;

    void route_register();
    void route_login();
    void route_actvities();
public:
    Server();
    ~Server();
    Server(const std::string &host, int port);
    void route();
    void stop();
    void listen();
};
