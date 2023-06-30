#pragma once

#include <string>
#include <vector>

struct Admin{
    std::string name = "";
    std::string surname = "";
    std::string login = "";
    std::string password = "";
    std::vector<int> activities = std::vector<int>();
};