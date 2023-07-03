//
//  StaffManager.hpp
//  StaffManagementSystem
//
//  Created by CX Lin on 2023/07/03.
//

#ifndef StaffManager_hpp
#define StaffManager_hpp

#include "Staff.hpp"
#include "Employee.hpp"
#include "Manager.hpp"
#include "Boss.hpp"

#include <vector>

#define FILENAME "StaffFile.csv"

class StaffManager {
public:
    // constructor
    StaffManager();
    // destructor
    ~StaffManager();
    
    /* parameters */
    // staff pointer vector
    std::vector<Staff *> staffVec;
    
    /* functions */
    // show menu
    void ShowMenu();
    // exit system
    void ExitSystem();
    // add staff
    void AddStaff();
    // save staff info to file
    void Save();
    // count staff from file
    int GetStaffNum();
    // read staff info from file
    void LoadStaff();
    // show staff info
    void ShowStaff();
    // delete staff
    void DeleteStaff();
    // check staff if exists
    int IsStaffExist(int ID);
    // edit staff info
    void EditStaff();
    // retrieve staff info
    void RetrieveStaff();
    // sort staff by ID
    void SortStaff();
    // clear file
    void ClearFile();
};

#endif /* StaffManager_hpp */
