#pragma once
#ifndef EMPLOYEEMANAGER_H
#define EMPLOYEEMANAGER_H

#include "UserManager.h"
#include <string>

class EmployeeManager : public UserManager {
public:
    void employeeLogin();
    void showEmployeeMenu(const string& username);

private:
    void showEmployeeInfo(const string& username);
    bool updatePasswordEmployee(const string& username);
    bool updatePasswordEmployeeFirstLogin(const string& username);
    void updatePassword(const string& username, const string& newPassword);
};

#endif
