#include "network/Server.hpp"
#include "network/Server.hpp"
#include "repositories/LocalDataRepositoryImpl.hpp"
#include "Utils.hpp"

void Server::route_register() {
    m_server->Post("/register_student", [this](const httplib::Request& req, httplib::Response& res) {
        std::string body = req.body;
        int result = this->m_dataSource->insertStudent(Utils::serialize_student(body));
        if(result == 0) {
            std::cout << body << std::endl;
            res.status = 409;
            res.set_content("{\"status\" : \"ERROR\" }", "application/json");

        }else{
            res.status = 200;
            res.set_content("{\"status\" : \"OK\" }", "application/json");
        }
    });

    m_server->Post("/register_admin", [this](const httplib::Request& req, httplib::Response& res) {
        std::string body = req.body;
        int result = this->m_dataSource->insertAdmin(Utils::serialize_admin(body));
        if (result == 0) {
            std::cout << body << std::endl;
            res.status = 409;
            res.set_content("{\"status\" : \"ERROR\" }", "application/json");

        }
        else {
            res.status = 200;
            res.set_content("{\"status\" : \"OK\" }", "application/json");
        }
    });
}

void Server::route_login() {
    m_server->Get("/login_student", [this](const httplib::Request& req, httplib::Response& res) {
        std::string login = req.get_param_value("login");
    std::string password = req.get_param_value("password");
        int result = this->m_dataSource->loginStudent(login, password);
        if (result != 0) {
            res.set_content("{\"status\" : \"OK\" }", "application/json");
        }else{
            res.set_content("{\"status\" : \"ERROR\" }", "application/json");

            res.status = 409;
        }
        }
    );
    m_server->Get("/login_admin", [this](const httplib::Request& req, httplib::Response& res) {
        std::string login = req.get_param_value("login");
        std::string password = req.get_param_value("password");
        int result = this->m_dataSource->loginAdmin(login, password);
        if (result != 0) {
            res.set_content("{\"status\" : \"OK\" }", "application/json");
        }
        else {
            res.set_content("{\"status\" : \"ERROR\" }", "application/json");
            res.status = 409;
        }
        }
    );
}

void Server::route_actvities()
{
    m_server->Get("/user_activities", [this](const httplib::Request& req, httplib::Response& res) {
        int id = std::stoi(req.get_param_value("id"));
        std::string str = this->m_dataSource->getUserActivities(id);
        res.set_content(str, "application/json");

        });

    m_server->Get("/admin_activities", [this](const httplib::Request& req, httplib::Response& res) {
        int id = std::stoi(req.get_param_value("id"));
        std::string str = this->m_dataSource->getAdminActivities(id);
        res.set_content(str, "application/json");

        });
    m_server->Get("/activities", [this](const httplib::Request& req, httplib::Response& res){
        std::string str = this->m_dataSource->getActivities();
        res.set_content(str, "application/json");
    });
    m_server->Post("/add_activity", [this](const httplib::Request& req, httplib::Response& res){
        int result = this->m_dataSource->insertActivity(Utils::serialize_activity_from_json(req.body));
        if (result == 0) {
            res.set_content("{\"status\" : \"ERROR\" }", "application/json");
            res.status = 409;
        }else{
            res.set_content("{\"status\" : \"OK\" }", "application/json");
        }
    });
    m_server->Get("/add_user_activity", [this](const httplib::Request& req, httplib::Response& res){
        int result = this->m_dataSource->updateUserActivities(std::stoi(req.get_param_value("id")), std::stoi(req.get_param_value("activity_id")));
        if (result == 0) {
            res.set_content("{\"status\" : \"ERROR\" }", "application/json");
            res.status = 409;
        }else{
            res.set_content("{\"status\" : \"OK\" }", "application/json");
        }

    });

    m_server->Get("/add_admin_activity", [this](const httplib::Request& req, httplib::Response& res){
        int result = this->m_dataSource->updateAdminActivities(std::stoi(req.get_param_value("id")), std::stoi(req.get_param_value("activity_id")));
        if (result == 0) {
            res.set_content("{\"status\" : \"ERROR\" }", "application/json");
            res.status = 409;
        }else{
            res.set_content("{\"status\" : \"OK\" }", "application/json");
        }
    });
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
    route_actvities();
}

void Server::stop() {

}

void Server::listen() {
    m_server->listen(m_host, m_port);
}
