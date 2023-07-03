//
//  main.cpp
//  StaffManagementSystem
//
//  Created by CX Lin on 2023/07/03.
//

#include "StaffManager.hpp"
#include "Staff.hpp"
#include "Employee.hpp"
#include "Manager.hpp"
#include "Boss.hpp"

#include <iostream>
#include <string>
#include <limits>

int main(int argc, const char *argv[]) {
    StaffManager sm;

    bool loopFlag = true;
    while(loopFlag) {
        sm.ShowMenu();
        
        std::cout << "Input\n> ";
        char choice;
        std::cin >> choice;
        // clear invalid input and continue to next while loop
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        switch(choice) {
            case '0':   // exit management system
                //sm.ExitSystem();
                std::cout << "\n** Thanks for using Staff Management System **\n" << std::endl;
                loopFlag = false;
                break;
            case '1':   // show staff information
                sm.ShowStaff();
                break;
            case '2':   // add staff
                sm.AddStaff();
                break;
            case '3':   // delete staff
                sm.DeleteStaff();
                break;
            case '4':   // edit staff information
                sm.EditStaff();
                break;
            case '5':   // retrieve a staff
                sm.RetrieveStaff();
                break;
            case '6':   // sort staff by its ID
                sm.SortStaff();
                break;
            case '7':   // clear staff database
                sm.ClearFile();
                break;
            default:
                std::cout << "\n** Invalid input. Please enter a number between 0 and 7 **\n" << std::endl;
                break;
        }
        // clear input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    return 0;
}
