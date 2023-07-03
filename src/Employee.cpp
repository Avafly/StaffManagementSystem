//
//  Employee.cpp
//  StaffManagementSystem
//
//  Created by CX Lin on 2023/07/03.
//

#include "Employee.hpp"

#include <iostream>
#include <string>
#include <iomanip>

// constructor
Employee::Employee(int ID, int deptID, std::string name) {
    this->ID = ID;
    this->name = name;
    this->deptID = deptID;
}

// show employee info
void Employee::ShowInfo() {
    std::cout << std::left << std::setw(10) << this->ID << std::setw(15) << "Employee" << this->name << std::endl;
}

std::string Employee::getDeptName() {
    return std::string("Employee");
}
