#include "AdminManager.h"
#include "utils.h"
#include <algorithm>
#include<regex>
void AdminManager::addEmployee() {
    ofstream add("Employees.txt", ios::app);
    ifstream is("Employees.txt");
    ofstream checkFirstLogin("FirstLogin.txt", ios::app);
    string username, password, name, address, phoneNumber, email;
    setColor(1); cout << "Nhap username: "; setColor(7); cin >> username;
    setColor(1); cout << "Nhap password: "; setColor(7);
    while (true) {
        password = inputPassword();

        if (password == "111111") {
            break;
        }
        else {
            setColor(4);
            cout << "Mat khau mac dinh phai la 111111, nhap lai: ";
        }
    }

    cin.ignore();
    setColor(1); cout << "Ho ten: "; setColor(7); getline(cin, name);
    setColor(1); cout << "Dia chi: "; setColor(7); getline(cin, address);
    setColor(1); cout << "So dien thoai: "; setColor(7); cin >> phoneNumber;
    while (true) {
        setColor(1); cout << "Nhap Email: "; setColor(7); cin >> email;

        // Mẫu regex kiểm tra định dạng email
        const regex emailPattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        if (regex_match(email, emailPattern)) {
            break; // Email hợp lệ, thoát vòng lặp
        }
        else {
            setColor(4);
            cout << "Email khong hop le! Vui long nhap lai." << endl;
        }
    }

    string storedUsername, storedPassword;
    while (is >> storedUsername >> storedPassword) {
        if (storedUsername == username) {
            setColor(4);
            cout << "Them that bai! Username vua nhap da ton tai." << endl;
            add.close();
            is.close();
            return;
        }
    }

    ofstream employeeFile(username + ".txt");
    employeeFile << name << endl;
    employeeFile << address << endl;
    employeeFile << phoneNumber << endl;
    employeeFile << email << endl;
    employeeFile.close();

    add << username << " " << password << endl;
    checkFirstLogin << username << endl;
    add.close();
    is.close();
    cout << "Da them thanh cong!" << endl;
}
void AdminManager::deleteEmployee() {
    string storedUsername, storedPassword;
    string username;
    bool found = false;
    setColor(1);
    cout << "Nhap username muon xoa: "; setColor(7); cin >> username;

    ifstream inputFile("Employees.txt");
    ofstream tempFile("temp.txt");
    while (inputFile >> storedUsername >> storedPassword) {
        if (storedUsername == username) {
            found = true;
        }
        else {
            tempFile << storedUsername << " " << storedPassword << endl;
        }
    }
    inputFile.close();
    tempFile.close();

    if (found) {
        remove((username + ".txt").c_str());
        remove("Employees.txt");
        rename("temp.txt", "Employees.txt");
        updateFirstLoginFile(username);
        setColor(2); cout << "Da xoa thanh cong!" << endl;
    }
    else {
        remove("temp.txt");
        setColor(4); cout << "Khong tim thay username!" << endl;
    }
}
void AdminManager::searchAndShowEmployee() {
    string username;
    cout << "Nhap username can tim kiem: ";
    setColor(7); cin >> username;

    vector<string> employees;
    ifstream inputFile("Employees.txt");
    string storedUsername, storedPassword;
    while (inputFile >> storedUsername >> storedPassword) {
        employees.push_back(storedUsername);
    }
    inputFile.close();

    sort(employees.begin(), employees.end());
    bool found = binarySearchEmployee(employees, username);

    if (found) {
        ifstream userFile(username + ".txt");
        string name, address, phoneNumber, email;
        getline(userFile, name);
        getline(userFile, address);
        getline(userFile, phoneNumber);
        getline(userFile, email);

        cout << "Thong tin nhan vien:" << endl;
        cout << "Username: " << username << endl;
        cout << "Ho ten: " << name << endl;
        cout << "Dia chi: " << address << endl;
        cout << "So dien thoai: " << phoneNumber << endl;
        cout << "Email: " << email << endl;
        userFile.close();
    }
    else {
        setColor(4);
        cout << "Khong tim thay nhan vien voi username da nhap!" << endl;
    }
}
void AdminManager::updateEmployeeInfo() {
    string username, name, address, phoneNumber, email;
    cout << "Nhap username can cap nhat thong tin: ";
    setColor(7); cin >> username;

    // Sử dụng tìm kiếm nhị phân
    vector<string> employees;
    ifstream inputFile("Employees.txt");
    string storedUsername, storedPassword;
    while (inputFile >> storedUsername >> storedPassword) {
        employees.push_back(storedUsername);
    }
    inputFile.close();

    // Sắp xếp danh sách username để tìm kiếm nhị phân
    sort(employees.begin(), employees.end());
    bool found = binary_search(employees.begin(), employees.end(), username);

    if (found) {
        ifstream inputFileUser(username + ".txt");
        string name, address, phoneNumber, email;
        getline(inputFileUser, name);
        getline(inputFileUser, address);
        getline(inputFileUser, phoneNumber);
        getline(inputFileUser, email);
        inputFileUser.close();

        int role;
        setColor(14); cout << "1. Ten" << endl;
        cout << "2. Dia chi" << endl;
        cout << "3. So dien thoai" << endl;
        cout << "4. Email" << endl;
        cout << "Nhap lua chon de cap nhat lai thong tin: ";
        setColor(7); cin >> role;
        cin.ignore();
        if (role == 1) {
            cout << "Nhap ten moi: ";
            getline(cin, name);
        }
        else if (role == 2) {
            cout << "Nhap dia chi moi: ";
            getline(cin, address);
        }
        else if (role == 3) {
            cout << "Nhap so dien thoai moi: ";
            getline(cin, phoneNumber);
        }
        else if (role == 4) {
            cout << "Nhap email moi: ";
            getline(cin, email);
        }
        else {
            setColor(4); cout << "Lua chon khong hop le.\n";
            return;
        }

        ofstream outputFileUser(username + ".txt");
        outputFileUser << name << endl;
        outputFileUser << address << endl;
        outputFileUser << phoneNumber << endl;
        outputFileUser << email << endl;
        outputFileUser.close();
        setColor(2); cout << "Cap nhat thong tin thanh cong!\n";
    }
    else {
        cout << "Khong tim thay username!" << endl;
    }
}
void AdminManager::showEmployee() {
    setColor(3); cout << endl << "* * * * * DANH SACH EMPLOYEE * * * * *" << endl;
    ifstream inputFile("Employees.txt");
    string storedUsername, storedPassword;

    while (inputFile >> storedUsername >> storedPassword) {
        setColor(13);  cout << "Username: "; setColor(7); cout << storedUsername << endl;
        ifstream userFile(storedUsername + ".txt");

        string name, address, phoneNumber, email;
        getline(userFile, name);
        getline(userFile, address);
        getline(userFile, phoneNumber);
        getline(userFile, email);

        setColor(13); cout << "Ho ten: "; setColor(7); cout << name << endl;
        setColor(13); cout << "Dia chi: "; setColor(7); cout << address << endl;
        setColor(13); cout << "So dien thoai: "; setColor(7); cout << phoneNumber << endl;
        setColor(13); cout << "Email: "; setColor(7); cout << email << endl;

        setColor(7); cout << "--------------------------------------";
        setColor(13); cout << endl;
        userFile.close();
    }
    inputFile.close();
}
void AdminManager::showAdminMenu() {
    while (1) {
        setColor(12);
        cout << "\n* * * * * * * MENU ADMIN * * * * * * *\n";
        setColor(7);
        cout << "       1. Them Employee\n";
        cout << "       2. Xoa Employee\n";
        cout << "       3. Tim Employee\n";
        cout << "       4. Cap nhat thong tin Employee\n";
        cout << "       5. Hien thi thong tin Employee\n";
        setColor(4);
        cout << "       6. Thoat\n";
        setColor(1);
        cout << "       Moi nhap lua chon: ";
        setColor(7); string role; cin >> role;

        if (role == "1") {
            addEmployee();
        }
        else if (role == "2") {
            deleteEmployee();
        }
        else if (role == "3") {
            searchAndShowEmployee();
        }
        else if (role == "4") {
            updateEmployeeInfo();
        }
        else if (role == "5") {
            showEmployee();
        }
        else if (role == "6") {

            cout << "Thoat thanh cong!";
            return;
        }
        else {
            setColor(4); cout << "Lua chon khong hop le" << endl;
        }
    }
}
void AdminManager::adminLogin() {
    setColor(10);
    cout << endl;
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
    cout << "*";
    setColor(14);
    cout << "           DANG NHAP ADMIN           ";
    setColor(10);
    cout << "*";
    cout << endl;
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
    string username, password;
    setColor(1);
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Username: ";
    setColor(7);
    getline(cin, username);
    setColor(1);
    cout << "Password: ";
    setColor(7);
    password = inputPassword();

    if (isAdmin(username, password)) {
        setColor(2);
        cout << "Dang nhap thanh cong voi vai tro Admin!\n";
        showAdminMenu();
    }
    else {
        setColor(4);
        cout << "Dang nhap that bai! Vui long thu lai\n";

        AdminManager::adminLogin();


    }
}
