#include "network/Server.hpp"
#include "network/Server.hpp"
#include "repositories/LocalDataRepositoryImpl.hpp"
#include "Utils.hpp"

void Server::route_register() {
    m_server->Post("/register_student", [this](const httplib::Request& req, httplib::Response& res) {
        std::string body = req.body;
        this->m_dataSource->insertStudent(Utils::serialize_student(body));
        res.set_content("Response body", "text/plain");
    });
}

void Server::route_login() {

}

Server::Server() {
    m_server = new httplib::Server();
    m_host = "localhost";
    m_port = 8080;
    m_dataSource = new LocalDataRepositoryImpl();
}

Server::~Server() {
    delete m_server;
}

Server::Server(const std::string &host, int port) {
    m_server = new httplib::Server();
    this->m_port = port;
    this->m_host = host;
    m_dataSource = new LocalDataRepositoryImpl();
}

void Server::route() {
    route_login();
    route_register();
}

void Server::stop() {

}

void Server::listen() {
    m_server->listen(m_host, m_port);
}
