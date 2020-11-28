#ifndef BANK_H
#define BANK_H
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <string.h>

using json = nlohmann::json;

class Bank {

public:
    Bank();
    void create_account();
    void update_inf_exs_account();
    void transactions();
    void check_det_acount();
    void rm_exs_account();
    void view_cust_list();

private:
    const std::string path = "bankfile.json";

    struct Person {
        int money = 0;
        std::string name, password, last_name, passport_number,
            date_of_birth, middle_name;
    };
};

#endif // BANK_H
