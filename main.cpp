#include "bank.h"

#include <fstream>
#include <iostream>

void print_Welcome()
{

    std::cout << "Enter 1 to create account\n"
              << "Enter 2 to update information to your account\n"
              << "Enter 3 transactions \n"
              << "Enter 4 to check your account details \n"
              << "Enter 5 to remove your account\n"
              << "Enter 6 to view customers list \n"
              << "Enter 7 to exit\n";
}

int main()
{

    Bank bobj;
    int num;

    bool exit = false;
    while (!exit) {
        print_Welcome();
        std::cin >> num;
        switch (num) {

        case 1:
            //create  account
            bobj.create_account();
            break;
        case 2:
            //update information of  existing account
            bobj.update_inf_exs_account();
            break;
        case 3:
            //for transactions
            bobj.transactions();
            break;
        case 4:

            //check the  details  of existing  account
            bobj.check_det_acount();
            break;
        case 5:
            bobj.rm_exs_account();
            //removing  existing  account
            break;
        case 6:
            //view customers  list
            bobj.view_cust_list();
            break;
        case 7:
            //exit
            exit = true;
            break;
        default:
            std::cout << "Please select correct paragraph\n";
        }
    }

    return 0;
}
