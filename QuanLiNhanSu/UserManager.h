#pragma once
#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class UserManager {
protected:
    string inputPassword();
    bool isAdmin(const string& username, const string& password);
    bool isEmployee(const string& username, const string& password);
    bool isFirstLogin(const string& username);
    void updateFirstLoginFile(const string& username);
};

#endif
