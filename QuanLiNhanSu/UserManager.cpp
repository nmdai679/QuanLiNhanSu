#include "UserManager.h"
#include "utils.h"
#include <conio.h>
#include <cstdio>
// Chuan hoa nhap mat khau vao thanh dau *
string UserManager::inputPassword() {
    string password;
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b' && !password.empty()) {
            cout << "\b \b";
            password.pop_back();
        }
        else if (ch != '\b') {
            password += ch;
            cout << '*';
        }
    }
    cout << endl;
    return password;
}

// Kiem tra nguoi dung co phai admin khong
bool UserManager::isAdmin(const string& username, const string& password) {
    ifstream file("Administrators.txt");
    string storedUsername, storedPassword;
    while (file >> storedUsername >> storedPassword) {
        if (storedUsername == username && storedPassword == password) {
            return true;
        }
    }
    return false;
}

// neu la nguoi dung
bool UserManager::isEmployee(const string& username, const string& password) {
    ifstream file("Employees.txt");
    string storedUsername, storedPassword;
    while (file >> storedUsername >> storedPassword) {
        if (storedUsername == username && storedPassword == password) {
            return true;
        }
    }
    return false;
}

// Kiem tra lan dang nhap dau tien
bool UserManager::isFirstLogin(const string& username) {
    ifstream file("FirstLogin.txt");
    string storedUsername;
    while (file >> storedUsername) {
        if (storedUsername == username) {
            return true;
        }
    }
    return false;
}

// Cap nhat lai file khi nguoi dung da dang nhap lan dau tien
void UserManager::updateFirstLoginFile(const string& username) {
    ifstream file("FirstLogin.txt");
    ofstream temp("temp.txt");
    string storedUsername;
    while (file >> storedUsername) {
        if (storedUsername != username) {
            temp << storedUsername << endl;
        }
    }
    file.close();
    temp.close();
    remove("FirstLogin.txt");
    rename("temp.txt", "FirstLogin.txt");
}
