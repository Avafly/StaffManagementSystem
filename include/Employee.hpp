//
//  Employee.hpp
//  StaffManagementSystem
//
//  Created by CX Lin on 2023/07/03.
//

#ifndef Employee_hpp
#define Employee_hpp

#include "Staff.hpp"

#include <string>

class Employee : public Staff {
public:
    // constructor
    Employee(int ID, int deptID, std::string name);
    
    // show employee info
    void ShowInfo() override;
    // get department name
    std::string getDeptName() override;
};

#endif /* Employee_hpp */
