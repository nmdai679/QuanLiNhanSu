#pragma once
#ifndef ADMINMANAGER_H
#define ADMINMANAGER_H

#include "UserManager.h"
#include <string>
#include <iostream>

class AdminManager : public UserManager {
public:
    void addEmployee();
    void deleteEmployee();
    void searchAndShowEmployee();
    void updateEmployeeInfo();
    void showEmployee();
    void showAdminMenu();
    void adminLogin();
};

#endif
