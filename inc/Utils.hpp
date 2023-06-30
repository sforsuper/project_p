#pragma once

#include <vector>
#include <string>
#include "entities/Student.h"
#include "entities/Admin.h"
#include "entities/Activity.h"

class Utils{
public:
    static std::vector<int> convert_string_to_vector_int(std::string str);
    static std::string convert_int_vector_to_string(std::vector<int> my_vector);

    static Student serialize_student(std::string str);
    static Admin serialize_admin(std::string str);
    static std::string deserialize_student(Student student);
    static std::string deserialize_admin(Admin admin);

    static std::string deserialize_activities(std::vector<Activity> activities);
    static std::vector<Activity> serialize_activities(std::string str);

    static std::string deserialize_activity(Activity object);
    static Activity serialize_activity(std::string str);

    static Activity serialize_activity_from_json(std::string str);
};