#pragma once

#include <vector>
#include <string>
#include "entities/Student.h"

class Utils{
public:
    static std::vector<int> convert_string_to_vector_int(std::string str);
    static std::string convert_int_vector_to_string(std::vector<int> my_vector);

    static Student serialize_student(std::string str);
    static std::string deserialize_student(Student student);
};