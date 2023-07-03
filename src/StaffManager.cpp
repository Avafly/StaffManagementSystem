//
//  StaffManager.cpp
//  StaffManagementSystem
//
//  Created by CX Lin on 2023/07/03.
//

#include "StaffManager.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

void ClearInput() {
    std::cin.clear(); // reset error state
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear the input buffer
}

// use polymorphism to create objects of different types
Staff *CreateStaff(int ID, int deptID, const std::string &name) {
    Staff *newStaff = nullptr;
    switch(deptID) {
        case 1:
            newStaff = new Employee(ID, deptID, name);
            break;
        case 2:
            newStaff = new Manager(ID, deptID, name);
            break;
        case 3:
            newStaff = new Boss(ID, deptID, name);
            break;
        default:
            newStaff = nullptr;
            break;
    }
    return newStaff;
}

StaffManager::StaffManager() {
    std::ifstream ifs(FILENAME, std::ios::in);
    
    // case 1: file does not exist
    if(!ifs.is_open()) {
        std::cout << "\n** Staff file does not exist **\n" << std::endl;
        this->staffVec = {};
        ifs.close();
        return;
    }
    // case 2: file exists, but is empty
    char ch;
    ifs >> ch;
    if(ifs.eof()) {
        std::cout << "\n** Staff file is empty **\n" << std::endl;
        this->staffVec = {};
        ifs.close();
        return;
    }
    // case 3: file exists and has content
    this->LoadStaff();
    std::cout << "\n** " << this->GetStaffNum() << " staff info has been loaded **\n" << std::endl;
}

StaffManager::~StaffManager() {
    if(!this->staffVec.empty()) {
        for(auto &object : this->staffVec) {    // delete object memory
            if(object) {
                delete object;
                object = nullptr;
            }
        }
        this->staffVec.clear(); // clear vector
    }
}

// show menu
void StaffManager::ShowMenu() {
    std::cout << "===================================" << std::endl;
    std::cout << "Welcome to staff management system" << std::endl;
    std::cout << "0. Exit System\t1. Show Staff" << std::endl;
    std::cout << "2. Add Staff \t3. Delete Staff" << std::endl;
    std::cout << "4. Edit Staff \t5. Retrieve Staff" << std::endl;
    std::cout << "6. Sort Staff \t7. Clear Staff File" << std::endl;
    std::cout << "===================================" << std::endl;
}

// exit system
// deprecated because exit(0) does not implement destructor function
void StaffManager::ExitSystem() {
    std::cout << "\n** Thanks for using Staff Management System **\n" << std::endl;
    exit(0);
}

// add staff
void StaffManager::AddStaff() {
    int newID = this->staffVec.empty() ? 1 : std::max(this->staffVec.back()->ID, this->staffVec.front()->ID) + 1;
    int newDeptID;
    std::string newName;
    
    std::cout << "Enter the new department" << std::endl;
    // fetch new staff's department ID and name
    while(true) {
        std::cout << "1. Employee\t2. Manager\t3. Boss\n> ";
        std::cin >> newDeptID;
        if(std::cin.fail() || newDeptID < 1 || newDeptID > 3) {
            std::cout << "** Invalid input, please enter 1, 2, or 3 **" << std::endl;
            ClearInput();
        }
        else {
            break;
        }
    }
    std::cout << "Enter the new name\n> ";
    std::cin >> newName;
    
    Staff *newStaff = CreateStaff(newID, newDeptID, newName);
    if(newStaff) {
        // add new staff to vector
        this->staffVec.push_back(newStaff);
        this->Save();
        std::cout << "\n** The staff has been added successfully **\n" << std::endl;
    }
}

// save staff info to file
void StaffManager::Save() {
    std::ofstream ofs;
    ofs.open(FILENAME, std::ios::out);
    
    for(const auto &staff : this->staffVec) {
        ofs << staff->ID << "," << staff->deptID << "," << staff->name << std::endl;
    }
    ofs.close();
}

// count staff
int StaffManager::GetStaffNum() {
    return static_cast<int>(this->staffVec.size());
}

// read staff info from file
void StaffManager::LoadStaff() {
    std::ifstream ifs(FILENAME, std::ios::in);
    
    int ID;
    int deptID;
    std::string name;
    
    // read csv file
    std::string line;
    while(std::getline(ifs, line)) {
        std::istringstream ss(line);
        std::string field;
        // ID
        std::getline(ss, field, ',');
        ID = std::stoi(field);
        // deptID
        std::getline(ss, field, ',');
        deptID = std::stoi(field);
        // name
        std::getline(ss, field, ',');
        name = field;
        
        Staff *staff = CreateStaff(ID, deptID, name);
        if(staff) {
            // add staff to vector
            this->staffVec.push_back(staff);
        }
    }
    
    ifs.close();
}

// show staff info
void StaffManager::ShowStaff() {
    std::cout << "\nStaff Information" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    std::cout << std::left << std::setw(10) << "ID" << std::setw(15) << "Department" << "Name" << std::endl;
    for(const auto &staff : this->staffVec) {
        staff->ShowInfo();
    }
    std::cout << "-----------------------------------\n" << std::endl;
}

// delete staff
void StaffManager::DeleteStaff() {
    if(this->staffVec.empty()) { // no staff available for deletion
        std::cout << "\n** Staff list is currently empty **\n" << std::endl;
    }
    else {
        int delID;
        
        // fetch the ID of the staff to be deleted
        while(true) {
            std::cout << "Enter the ID of staff for deletion\n> ";
            std::cin >> delID;
            if(std::cin.fail() || delID <= 0) {
                std::cout << "** Invalid input, please enter a positive integer **" << std::endl;
                ClearInput();
            }
            else {
                break;
            }
        }
        
        int index = this->IsStaffExist(delID);
        if(index != -1) {   // if this staff exists
            // delete this staff
            if(this->staffVec[index]) {
                delete this->staffVec[index];
                this->staffVec[index] = nullptr;
            }
            this->staffVec.erase(this->staffVec.begin() + index);
            // sync data to file
            this->Save();
            std::cout << "\n** The staff has been deleted successfully **\n" << std::endl;
        }
        else {
            std::cout << "\n** This staff was not found **\n" << std::endl;
        }
    }
}

// check staff if exists
int StaffManager::IsStaffExist(int ID) {
    int index = -1;
    for(int i = 0; i < this->staffVec.size(); ++i) {
        if(this->staffVec[i]->ID == ID) {
            index = i;
            break;
        }
    }
    
    return index;
}

// edit staff info
void StaffManager::EditStaff() {
    if(this->staffVec.empty()) { // no staff available for editing
        std::cout << "\n** Staff list is currently empty **\n" << std::endl;
    }
    else {
        int editID;
        
        // fetch the ID of the staff to be edited
        while(true) {
            std::cout << "Enter the ID of staff for editing\n> ";
            std::cin >> editID;
            if(std::cin.fail() || editID <= 0) {
                std::cout << "** Invalid input, please enter a positive integer **" << std::endl;
                ClearInput();
            }
            else {
                break;
            }
        }
        
        int index = this->IsStaffExist(editID);
        if(index != -1) {
            int newDeptID;
            std::string newName;
            
            // fetch new staff's department ID and name
            while(true) {
                std::cout << "New department" << std::endl;
                std::cout << "1. Employee\t2. Manager\t3. Boss\n> ";
                std::cin >> newDeptID;
                if(std::cin.fail() || newDeptID < 1 || newDeptID > 3) {
                    std::cout << "** Invalid input, please enter 1, 2, or 3 **" << std::endl;
                    ClearInput();
                }
                else {
                    break;
                }
            }
            std::cout << "New name\n> ";
            std::cin >> newName;
            
            Staff *staff = CreateStaff(editID, newDeptID, newName);
            // update staff information
            if(staff) {
                // delete previous staff information
                if(this->staffVec[index]) {
                    delete this->staffVec[index];
                    this->staffVec[index] = nullptr;
                }
                // insert new staff information
                this->staffVec[index] = staff;
                // sync data to file
                this->Save();
                
                std::cout << "\n** The staff info has been edited successfully **\n" << std::endl;
            }
        }
        else {
            std::cout << "\n** This staff was not found **\n" << std::endl;
        }
    }
}

// retrieve staff info
void StaffManager::RetrieveStaff() {
    if(this->staffVec.empty()) { // no staff available for searching
        std::cout << "\n** Staff list is currently empty **\n" << std::endl;
    }
    else {
        std::cout << "Select search method" << std::endl;
        int select = 0;
        // fetch select
        while(true) {
            std::cout << "1. Search by ID\t2. Search by name\n> ";
            std::cin >> select;
            if(std::cin.fail() || select < 1 || select > 2) {
                std::cout << "** Invalid input, please enter 1 or 2 **" << std::endl;
                ClearInput();
            }
            else {
                break;
            }
        }
        
        if(select == 1) {
            // search by ID
            int ID;
            // fetch the ID of the staff to be searched
            while(true) {
                std::cout << "Enter the ID of the staff to be searched\n> ";
                std::cin >> ID;
                if(std::cin.fail() || ID <= 0) {
                    std::cout << "** Invalid input, please enter a positive integer **" << std::endl;
                    ClearInput();
                }
                else {
                    break;
                }
            }
            
            int index = this->IsStaffExist(ID);
            if(index != -1) {
                // found the staff
                std::cout << "\nStaff Information" << std::endl;
                std::cout << "-----------------------------------" << std::endl;
                std::cout << std::left << std::setw(10) << "ID" << std::setw(15) << "Department" << "Name" << std::endl;
                this->staffVec[index]->ShowInfo();
                std::cout << "-----------------------------------\n" << std::endl;
            }
            else {
                std::cout << "\n** '" << ID << "' was not found **\n" << std::endl;
            }
        }
        else {
            // search by name
            std::cout << "Enter the name of staff for searching\n> ";
            std::string name;
            std::cin >> name;
            
            bool isFind = false;
            std::vector<Staff *> tmp;
            for(const auto &staff : this->staffVec) {
                if(staff->name == name) {   // add staff to tmp
                    isFind = true;
                    tmp.push_back(staff);
                }
            }
            // show matched staff(s)
            if(isFind) {
                std::cout << "\nStaff Information" << std::endl;
                std::cout << "-----------------------------------" << std::endl;
                std::cout << std::left << std::setw(10) << "ID" << std::setw(15) << "Department" << "Name" << std::endl;
                for(auto &staff : tmp) {
                    staff->ShowInfo();
                }
                std::cout << "-----------------------------------\n" << std::endl;
            }
            else {
                std::cout << "\n** '" << name << "' was not found **\n" << std::endl;
            }
        }
    }
}

// sort staff by ID
void StaffManager::SortStaff() {
    if(this->staffVec.empty()) { // no staff available for sorting
        std::cout << "\n** Staff list is currently empty **\n" << std::endl;
    }
    else {
        std::cout << "Select sorting method" << std::endl;
        int select = 0;
        // fetch select
        while(true) {
            std::cout << "1. Ascending\t2. Descending\n> ";
            std::cin >> select;
            if(std::cin.fail() || select < 1 || select > 2) {
                std::cout << "** Invalid input, please enter 1 or 2 **" << std::endl;
                ClearInput();
            }
            else {
                break;
            }
        }
        
        // sort
        if(select == 1) {   // ascending
            std::sort(this->staffVec.begin(), this->staffVec.end(), [](const Staff *a, const Staff *b) {
                return a->ID < b->ID;
            });
        }
        else {              // descending
            std::sort(this->staffVec.begin(), this->staffVec.end(), [](const Staff *a, const Staff *b) {
                return a->ID > b->ID;
            });
        }
        this->Save();
        std::cout << "\n** Staffs has been sorted successfully **\n" << std::endl;
    }
}

// clear file
void StaffManager::ClearFile() {
    std::cout << "You are about to permanently delete the staff file" << std::endl;
    std::cout << "Are you sure you want to continue?" << std::endl;
    
    int select = 0;
    // fetch select
    while(true) {
        std::cout << "1. Confirm\t2. Cancel\n> ";
        std::cin >> select;
        if(std::cin.fail() || select < 1 || select > 2) {
            std::cout << "** Invalid input, please enter 1 or 2 **" << std::endl;
            ClearInput();
        }
        else {
            break;
        }
    }
    
    if(select == 1) {   // clear staff file
        std::ofstream ofs(FILENAME, std::ios::out);
        ofs.close();
        // free the memory
        if(!this->staffVec.empty()) {
            for(auto &staff : this->staffVec) {
                if(staff) {
                    delete staff;
                    staff = nullptr;
                }
            }
            this->staffVec.clear();
        }
        
        std::cout << "\n** The staff data has been cleared successfully **\n" << std::endl;
    }
}
