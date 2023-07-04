//
//  Manager.cpp
//  StaffManagementSystem
//
//  Created by CX Lin on 2023/07/03.
//

#include "Manager.hpp"

#include <iostream>
#include <string>
#include <iomanip>

// constructor
Manager::Manager(int ID, int deptID, std::string name) {
    this->ID = ID;
    this->name = name;
    this->deptID = deptID;
}

// show Manager info
void Manager::ShowInfo() {
    std::cout << std::left << std::setw(10) << this->ID << std::setw(15) << this->getDeptName() << this->name << std::endl;
}

std::string Manager::getDeptName() {
    return std::string("Manager");
}
