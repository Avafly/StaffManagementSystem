//
//  Boss.hpp
//  StaffManagementSystem
//
//  Created by CX Lin on 2023/07/03.
//

#ifndef Boss_hpp
#define Boss_hpp

#include "Staff.hpp"

#include <string>

class Boss : public Staff {
public:
    // constructor
    Boss(int ID, int deptID, std::string name);
    
    // show manager info
    void ShowInfo() override;
    // get department name
    std::string getDeptName() override;
};

#endif /* Boss_hpp */
