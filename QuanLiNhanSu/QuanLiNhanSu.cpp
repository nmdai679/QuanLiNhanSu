#include "AdminManager.h"
#include "EmployeeManager.h"
#include "utils.h"

int main() {

    display();
    AdminManager adminManager;
    EmployeeManager employeeManager;
    int role;
    setColor(10);
    
        cout << "\n* * * * * * * * * * * * * * * * * * * *\n";
        cout << "*";
        setColor(14); cout << "    CHUONG TRINH QUAN LY NHAN SU    ";
        setColor(10); cout << " *\n";
        cout << "* * * * * * * * * * * * * * * * * * * *\n";
        setColor(7);
        cout << "1. Dang nhap voi vai tro Admin\n";
        cout << "2. Dang nhap voi vai tro Employee\n";
        setColor(12);
        cout << "3. Thoat\n";
        setColor(1); cout << "Nhap lua chon: ";
        setColor(7); cin >> role;
        if (role == 1) {
            adminManager.adminLogin();
        }
        else if (role == 2) {
            employeeManager.employeeLogin();
        }
        else if (role == 3) {
            return 0;
        }
        else {
            setColor(4); cout << "Lua chon khong hop le.\n";
        }
    

    return 0;
}
