#pragma once
#include "entities/Student.h"

class LocalDataRepository {
public:
    virtual void insertStudent(Student student) = 0;
};
