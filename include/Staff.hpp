//
//  Staff.h
//  StaffManagementSystem
//
//  Created by CX Lin on 2023/07/03.
//

#ifndef Staff_h
#define Staff_h

#include <string>

// staff abstrct class
class Staff {
public:
    // destructor
    virtual ~Staff() {}
    
    // staff ID
    int ID;
    // staff department
    int deptID;
    // staff name
    std::string name;
    
    // show staff info
    virtual void ShowInfo() = 0;
    // show department name
    virtual std::string getDeptName() = 0;
};

#endif /* Staff_h */
