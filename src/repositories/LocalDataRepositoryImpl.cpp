#include "repositories/LocalDataRepositoryImpl.hpp"
#include "Utils.hpp"
#include <iostream>
#include <sstream>
#include<string.h>
LocalDataRepositoryImpl::LocalDataRepositoryImpl() {
    m_database = new Database("data.db");
    m_database->open();
}

int LocalDataRepositoryImpl::insertStudent(Student student) {
    std::string sql = std::string ("INSERT INTO users (user_name,user_surname,login,password,activities) ") +
                      "VALUES (" + "'" + student.name + "', '" + student.surname + "', '"
                      + student.login + "', '" + student.password + "', '" + Utils::convert_int_vector_to_string(student.activities) + "')";
    int res = m_database->exec(sql);
    std::cout << "res" << res << std::endl;
    return res;
}

int LocalDataRepositoryImpl::insertAdmin(Admin admin)
{
    std::string sql = std::string("INSERT INTO admins (name,surname,login,password,activities) ") +
        "VALUES (" + "'" + admin.name + "', '" + admin.surname + "', '"
        + admin.login + "', '" + admin.password + "', '" + Utils::convert_int_vector_to_string(admin.activities) + "')";
    int res = m_database->exec(sql);
    std::cout << "res" << res << std::endl;
    return res;
}

int LocalDataRepositoryImpl::loginStudent(std::string login, std::string password)
{
    bool flag = false;
    auto lambda = [](void* data, int argc, char** argv, char** azColName) {
        bool* userExists = static_cast<bool*>(data);
        if (argc > 0) {
            for (int i = 0; i < argc; i++) {
                std::cout << argv[i] << std::endl;
            }
            *userExists = true;
        }
        else {
            *userExists = false;
        }
        return 0;
    };
    std::stringstream ss;
    ss << "SELECT * FROM users WHERE login = \"" << login << "\" AND password = \"" << password << "\"";
    std::string sql(ss.str());
    int res = m_database->exec(sql, lambda, &flag);
    if (flag == false){
        return 0;
    }else{
        return 1;
    }
}

int LocalDataRepositoryImpl::loginAdmin(std::string login, std::string password)
{
    bool flag = false;
    auto lambda = [](void* data, int argc, char** argv, char** azColName) {
        bool* userExists = static_cast<bool*>(data);
        if (argc > 0) {
            for (int i = 0; i < argc; i++) {
                std::cout << argv[i] << std::endl;
            }
            *userExists = true;
        }
        else {
            *userExists = 0;
        }
        return 0;
    };
    std::stringstream ss;
    ss << "SELECT * FROM admins WHERE login = \"" << login << "\" AND password = \"" << password << "\"";
    std::string sql(ss.str());
    int res = m_database->exec<bool>(sql, lambda, &flag);
    if (flag == false) {
        std::cout << "False" << std::endl;
    }
    else {
        std::cout << "True" << std::endl;
    }
    if (flag == false){
        return 0;
    }else{
        return 1;
    }
}

std::string LocalDataRepositoryImpl::getUserActivities(int id)
{
    std::string res_string = "";

    auto lambda = [](void* data, int argc, char** argv, char** azColName) {
        std::string* userActivities = static_cast<std::string*>(data);
        *userActivities = argv[0];
        return 0;
    };

    std::stringstream ss;
    ss << "SELECT activities FROM students WHERE id = " << id << ";";
    std::string sql(ss.str());
    int res = m_database->exec<std::string>(sql, lambda, &res_string);

    std::stringstream ss1;
    ss1 << "SELECT * FROM users WHERE activities in (" << res_string << ")";
    sql = ss.str();

    std::vector<Activity> activities;
    auto lambda2 = [](void* data, int argc, char** argv, char** azColName) {
        std::vector<Activity>* userActivities = static_cast<std::vector<Activity>*>(data);
        Activity activity;
        activity.id = std::stoi(argv[0]);
        activity.name = argv[1];
        activity.description = argv[2];
        activity.admin_id = std::stoi(argv[3]);
        userActivities->push_back(activity);
        return 0;
    };
    m_database->exec(sql, lambda2, &activities);
    return Utils::deserialize_activities(activities);
}

std::string LocalDataRepositoryImpl::getAdminActivities(int id)
{
    std::string res_string = "";

    auto lambda = [](void* data, int argc, char** argv, char** azColName) {
        std::string* userActivities = static_cast<std::string*>(data);
        *userActivities = argv[0];
        return 0;
    };

    std::stringstream ss;
    ss << "SELECT activities FROM admins WHERE id = " << id << ";";
    std::string sql(ss.str());
    int res = m_database->exec<std::string>(sql, lambda, &res_string);
    std::stringstream ss1;
    ss1 << "SELECT * FROM admins WHERE activities in (" << res_string << ")";
    sql = ss1.str();
    std::cout << sql;
    std::vector<Activity> activities;
    auto lambda2 = [](void* data, int argc, char** argv, char** azColName) {
        std::vector<Activity>* userActivities = static_cast<std::vector<Activity>*>(data);
        Activity activity;
        activity.id = std::stoi(argv[0]);
        activity.name = argv[1];
        activity.description = argv[2];
        activity.admin_id = std::stoi(argv[3]);
        userActivities->push_back(activity);
        return 0;
    };
    m_database->exec(sql, lambda2, &activities);
    return Utils::deserialize_activities(activities);
}

std::string LocalDataRepositoryImpl::getActivities() {

    std::vector<Activity> activities;
    auto lambda = [](void* data, int argc, char** argv, char** azColName) {
        std::vector<Activity>* userActivities = static_cast<std::vector<Activity>*>(data);
        Activity activity;
        activity.id = std::stoi(argv[0]);
        activity.name = argv[1];
        activity.description = argv[2];
        activity.admin_id = std::stoi(argv[3]);
        userActivities->push_back(activity);
        return 0;
    };
    std::stringstream ss;
    ss << "SELECT * FROM activities;";
    std::string sql(ss.str());
    m_database->exec(sql, lambda, &activities);
    std::cout << Utils::deserialize_activities(activities);
    std::cout << activities.size();
    return Utils::deserialize_activities(activities);
}

int LocalDataRepositoryImpl::insertActivity(Activity activity) {
    std::stringstream ss;
    ss << "INSERT INTO activities (name, description, admin_id) VALUES (\"" << activity.name
        << "\" , \"" << activity.description << "\" , " << activity.admin_id << ");" ;
    std::string sql(ss.str());
    int res = m_database->exec(sql);
    return res;
}

int LocalDataRepositoryImpl::updateUserActivities(int user_id, int activity_id) {
    std::string res_string = "";

    auto lambda = [](void* data, int argc, char** argv, char** azColName) {
        std::string* userActivities = static_cast<std::string*>(data);
        *userActivities = argv[0];
        return 0;
    };

    std::stringstream ss;
    ss << "SELECT activities FROM users WHERE id = " << user_id << ";";
    std::string sql(ss.str());
    int res = m_database->exec<std::string>(sql, lambda, &res_string);
    std::stringstream ss1;

    ss1 << "UPDATE users SET activities = \"" << res_string << " " << activity_id << "\" WHERE id=" << user_id << ";";
    sql = ss1.str();
    res = m_database->exec(sql);
    return res;
}

int LocalDataRepositoryImpl::updateAdminActivities(int user_id, int activity_id) {
    std::string res_string = "";

    auto lambda = [](void* data, int argc, char** argv, char** azColName) {
        std::string* userActivities = static_cast<std::string*>(data);
        *userActivities = argv[0];
        return 0;
    };

    std::stringstream ss;
    ss << "SELECT activities FROM admins WHERE id = " << user_id << ";";
    std::string sql(ss.str());
    int res = m_database->exec<std::string>(sql, lambda, &res_string);
    std::stringstream ss1;

    ss1 << "UPDATE admins SET activities = \"" << res_string << " " << activity_id << "\" WHERE id=" << user_id << ";";
    sql = ss1.str();
    res = m_database->exec(sql);
    return res;
}


