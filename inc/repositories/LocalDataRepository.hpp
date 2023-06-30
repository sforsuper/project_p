#pragma once
#include "entities/Student.h"
#include "entities/Admin.h"
#include "entities/Activity.h"

class LocalDataRepository {
public:
    virtual int insertStudent(Student student) = 0;
    virtual int insertAdmin(Admin admin) = 0;
    virtual int loginStudent(std::string login, std::string password) = 0;
    virtual int loginAdmin(std::string login, std::string password) = 0;

    virtual std::string getUserActivities(int id) = 0;
    virtual std::string getAdminActivities(int id) = 0;
    virtual std::string getActivities() = 0;
    virtual int insertActivity(Activity activity) = 0;
    virtual int updateUserActivities(int user_id, int activity_id) = 0;
    virtual int updateAdminActivities(int user_id, int activity_id) = 0;
};