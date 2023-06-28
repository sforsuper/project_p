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

std::string Utils::deserialize_student(Student student) {
    nlohmann::json j{};
    j["name"] = student.name;
    j["surname"] = student.surname;
    j["login"] = student.login;
    j["password"] = student.password;
    j["activities"] = convert_int_vector_to_string(student.activities);
    return j.dump();
}

