#include "json/json.hpp"
#include "Utils.hpp"
#include <sstream>
#include <iterator>
std::vector<int> Utils::convert_string_to_vector_int(std::string str) {
    std::vector<int> vector;
    int n;
    std::istringstream ss(str);
    while(ss >> n) vector.push_back(n);
    return vector;
}

std::string Utils::convert_int_vector_to_string(std::vector<int> my_vector) {
    std::stringstream result;
    std::copy(my_vector.begin(), my_vector.end(), std::ostream_iterator<int>(result, " "));
    return result.str().substr(0, result.str().length()-1);
}

Student Utils::serialize_student(std::string str) {
    Student s;
    nlohmann::json json = nlohmann::json::parse(str);
    s.name = json["name"].get<std::string>();
    s.login = json["login"].get<std::string>();
    s.password = json["password"].get<std::string>();
    s.surname = json["surname"].get<std::string>();
    s.activities = convert_string_to_vector_int(json["activities"].get<std::string>());
    return s;
}
Admin Utils::serialize_admin(std::string str) {
    Admin s;
    nlohmann::json json = nlohmann::json::parse(str);
    s.name = json["name"].get<std::string>();
    s.login = json["login"].get<std::string>();
    s.password = json["password"].get<std::string>();
    s.surname = json["surname"].get<std::string>();
    s.activities = convert_string_to_vector_int(json["activities"].get<std::string>());
    return s;
}

std::string Utils::deserialize_student(Student student) {
    nlohmann::json j{};
    j["name"] = student.name;
    j["surname"] = student.surname;
    j["login"] = student.login;
    j["password"] = student.password;
    j["activities"] = convert_int_vector_to_string(student.activities);
    return j.dump();
}


std::string Utils::deserialize_admin(Admin admin) {
    nlohmann::json j{};
    j["name"] = admin.name;
    j["surname"] = admin.surname;
    j["login"] = admin.login;
    j["password"] = admin.password;
    j["activities"] = convert_int_vector_to_string(admin.activities);
    return j.dump();
}

std::string Utils::deserialize_activities(std::vector<Activity> activities){
    nlohmann::json JsonObjects = nlohmann::json::array();
    for (const auto & object:activities){
        nlohmann::json j1;
        j1["id"] = object.id;
        j1["admin_id"] = object.admin_id;
        j1["name"] = object.name;
        j1["description"] = object.description;
        JsonObjects.push_back(j1);
    }
    return JsonObjects.dump();
}


std::string Utils::deserialize_activity(Activity object) {
    nlohmann::json j{};
    j["id"] = object.id;
    j["admin_id"] = object.admin_id;
    j["name"] = object.name;
    j["description"] = object.description;
    return j.dump();
}


Activity Utils::serialize_activity(std::string str) {
    Activity s;
    nlohmann::json json = nlohmann::json::parse(str);
    s.name = json["name"].get<std::string>();
    s.description = json["description"].get<std::string>();
    s.id = json["id"].get<int>();
    s.admin_id = json["admin_id"].get<int>();
    return s;
}

Activity Utils::serialize_activity_from_json(std::string str) {
    Activity s;
    nlohmann::json json = nlohmann::json::parse(str);
    s.name = json["name"].get<std::string>();
    s.description = json["description"].get<std::string>();
    s.admin_id = json["admin_id"].get<int>();
    return s;
}


