//
//  Manager.hpp
//  StaffManagementSystem
//
//  Created by CX Lin on 2023/07/03.
//

#ifndef Manager_hpp
#define Manager_hpp

#include "Staff.hpp"

#include <string>

class Manager : public Staff {
public:
    // constructor
    Manager(int ID, int deptID, std::string name);
    
    // show manager info
    void ShowInfo() override;
    // get department name
    std::string getDeptName() override;
};

#endif /* Manager_hpp */
