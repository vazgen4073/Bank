#include "bank.h"

#include <fstream>
#include <iostream>

void print_Welcome()
{

    std::cout << "Enter 1 to create account\n"
              << "Enter 2 to update information to your account\n"
              << "Enter 3 to see your transactions \n"
              << "Enter 4 to check your account details \n"
              << "Enter 5 to rwmove your account\n"
              << "Enter 6 to view client  list \n"
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
            break;
        case 4:

            //check the  details  of existing  account
            break;
        case 5:

            //removing  existing  account
            break;
        case 6:
            //view customers  list
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
