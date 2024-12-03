#include "EmployeeManager.h"
#include "utils.h"

void EmployeeManager::employeeLogin() {
    string username, password;
        int attempts = 0;

        while(attempts < 3){
            setColor(10);
            cout << "* * * * * * * * * * * * * * * * * * * *\n";
            cout << "*";
            setColor(14);
            cout << "          DANG NHAP EMPLOYEE         ";
            setColor(10);
            cout << "*";
            cout << endl;
            cout << "* * * * * * * * * * * * * * * * * * * *\n";
            setColor(1);
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Username: ";
            setColor(7);
            getline(cin, username);
            setColor(1);

            cout << "Password: ";
            setColor(7);
            password = inputPassword();

        if (isEmployee(username, password)) {
            if (isFirstLogin(username)) {
                cout << "Day la lan dang nhap dau tien. Vui long cap nhat lai mat khau!" << endl;
                if(updatePasswordEmployeeFirstLogin(username) == true){
                    updateFirstLoginFile(username);
                    
                } 
                showEmployeeMenu(username);        
                attempts += 3;       
            }
            else{
                setColor(2);
                cout << "Dang nhap thanh cong voi vai tro Employee!\n";
                showEmployeeMenu(username);
                return;
            }
            
        } 
        else {
            setColor(4);
            attempts++;
            cout << "Dang nhap that bai!\n";
            if(attempts == 3){
            setColor(4);
            cout << "Ban da nhap sai 3 lan, vui long thu lai sau!" << endl;
            return;
        }
        }
        }
}
void EmployeeManager::showEmployeeMenu(const string& username) {
    while (1) {
        int role;
        setColor(9);
        cout << "\n* * * * * * * MENU EMPLOYEE * * * * * * *\n";
        setColor(7);
        cout << "1. Xem thong tin tai khoan\n";
        cout << "2. Doi mat khau\n";
        setColor(4);
        cout << "3. Thoat\n";
        setColor(1);
        cout << "Nhap lua chon: "; setColor(7); cin >> role;
        setColor(1);
        if (role == 1) {
            showEmployeeInfo(username);
        }
        else if (role == 2) {
            updatePasswordEmployee(username);
        }
        else if (role == 3) {
            return;
        }
        else {
            setColor(4);
            cout << "Lua chon khong hop le.\n";
        }
    }
}
void EmployeeManager::showEmployeeInfo(const string& username) {
    ifstream inputFile((username + ".txt").c_str());
    string name, address, phoneNumber, email;
    getline(inputFile, name);
    getline(inputFile, address);
    getline(inputFile, phoneNumber);
    getline(inputFile, email);
    setColor(10);
    cout << "-----------THONG TIN TAI KHOAN-----------\n";
    setColor(3);
    cout << "Username: ";
    setColor(7);
    cout<< username << endl;
    setColor(3);
    cout << "Ho ten: ";
    setColor(7);
    cout<< name << endl;
    setColor(3);
    cout << "Dia chi: ";
    setColor(7);
    cout<< address << endl;
    setColor(3);
    cout << "So dien thoai: ";
    setColor(7);
   cout << phoneNumber << endl;
    setColor(3);
    cout << "Email: ";
    setColor(7);
   cout << email << endl;
    inputFile.close();
}
bool EmployeeManager::updatePasswordEmployee(const string& username) {
    string currentPassword;
    cout << "Nhap mat khau hien tai: ";
    setColor(7);
    currentPassword = inputPassword();

    // if(!isEmployee(username, currentPassword)){
    //     cout << "Mat khau hien tai khong chinh xac"<< endl;
    //     return false;
    // }

    while (!isEmployee(username, currentPassword)) {
        setColor(4);
        cout << "Mat khau khong chinh xac. Vui long nhap lai: ";
        setColor(7);
        currentPassword = inputPassword();
    }


    string newPassword, checkNewPassword;
    setColor(1);
    cout << "Nhap mat khau moi: ";
    setColor(7);
    newPassword = inputPassword();
    setColor(1);
    cout << "Xac nhan lai mat khau moi: ";
    setColor(7);
    checkNewPassword = inputPassword();
    if (newPassword == checkNewPassword) {
        updatePassword(username, newPassword);
        setColor(4);
        cout << "Cap nhat mat khau thanh cong!" << endl;
        return true;
    }
    else {
        setColor(4);
        cout << "Mat khau khong trung khop. Vui long nhap lai" << endl;
        
        updatePasswordEmployeeFirstLogin(username);
    }
    return false;
}
bool EmployeeManager::updatePasswordEmployeeFirstLogin(const string& username) {
    string newPassword, checkNewPassword;
    setColor(1);
    cout << "Nhap mat khau moi: ";
    setColor(7);
    newPassword = inputPassword();
    setColor(1);
    cout << "Xac nhan lai mat khau moi: ";
    setColor(7);
    checkNewPassword = inputPassword();
    if (newPassword == checkNewPassword) {
        updatePassword(username, newPassword);
        setColor(4);
        cout << "Cap nhat mat khau thanh cong!" << endl;
        return true;
    }
    else {
        setColor(4);
        cout << "Mat khau khong trung khop. Vui long nhap lai" << endl;
        updatePasswordEmployeeFirstLogin(username);
    }
    return false;
}
void EmployeeManager::updatePassword(const string& username, const string& newPassword) {
    ifstream inputFile("Employees.txt");
    ofstream tempFile("temp.txt");
    string storedUsername, storedPassword;
    while (inputFile >> storedUsername >> storedPassword) {
        if (storedUsername == username) {
            tempFile << storedUsername << " " << newPassword << endl;
        }
        else {
            tempFile << storedUsername << " " << storedPassword << endl;
        }
    }
    inputFile.close();
    tempFile.close();
    remove("Employees.txt");
    rename("temp.txt", "Employees.txt");
}
