//
//  Boss.cpp
//  StaffManagementSystem
//
//  Created by CX Lin on 2023/07/03.
//

#include "Boss.hpp"

#include <iostream>
#include <string>
#include <iomanip>

// constructor
Boss::Boss(int ID, int deptID, std::string name) {
    this->ID = ID;
    this->name = name;
    this->deptID = deptID;
}

// show Boss info
void Boss::ShowInfo() {
//    std::cout << "Staff ID: " << this->ID << " | "
//              << "Staff Name: " << this->name << " | "
//              << "Staff Department: " << this->getDeptName() << std::endl;
    std::cout << std::left << std::setw(10) << this->ID << std::setw(15) << "Boss" << this->name << std::endl;
}

std::string Boss::getDeptName() {
    return std::string("Employee");
}
