#include "bank.h"
#include <exception>
#include <iomanip>
#include <iostream>

void Bank::create_account()
{
    json j;
    Person ps;

    std::ifstream fin;
    fin.open(path);
    bool Isempty = false;
    if (!fin.is_open()) {
        std::ofstream out;
        Isempty = true;
        out.open(path, std::ios::out);
        if (!out.is_open()) {
            std::cout << "Cannot open file!\n";
            exit(1);
        }
        out.close();
    }

    fin.open(path);

    if (!fin.is_open()) {
        std::cout << "Cannot open file\n";
        exit(1);
    }
    std::string password, cnfpassword;

    std::system("clear");
    std::cout << "Please enter your name \n";
    std::cin >> ps.name;
    std::system("clear");
    std::cout << "Please enter your last name \n";
    std::cin >> ps.last_name;
    std::system("clear");
    std::cout << "Please enter your middle name \n";
    std::cin >> ps.middle_name;
    std::system("clear");
    std::cout << "Please enter your passport number \n";
    std::cin >> ps.passport_number;
    std::cin.ignore();
    std::system("clear");
    std::cout << "Please enter your date of birth \n";
    getline(std::cin, ps.date_of_birth);

    std::system("clear");
    bool passisok = true;
    do {
        if (!passisok) {
            std::cout << "Passwords do not match \n";
        }
        passisok = false;
        std::cout << "Please create password\n";
        std::cin >> password;
        std::cout << "Please confirm password\n";
        std::cin >> cnfpassword;
    } while (password != cnfpassword);

    if (!Isempty) {
        fin >> j;
    }
    ps.password = password;

    j[ps.passport_number] = {
        { "Password", ps.password },
        { "Name", ps.name },
        { "Middle Name", ps.middle_name },
        { "Last Name", ps.last_name },
        { "Date of birth", ps.date_of_birth },
        { "Deposit", ps.money },
        { "Transactions", { 0 } }
    };

    fin.close();
    std::ofstream out;
    out.open(path);
    if (!out.is_open()) {
        std::cout << "Cannot open file\n";
        exit(1);
    }
    out << j.dump(4) << "\n";

    out.close();

    std::system("clear");
    std::cout << "Your account created successesfully !\n";
}

void Bank::update_inf_exs_account()
{

    std::ifstream finout;
    finout.open("bankfile.json");

    if (!finout) {
        std::cout << "Cannot open file!\n";
        exit(1);
    }

    json j;
    finout >> j;
    finout.close();
    std::string passnum, password;

    int passctr = 3;
    bool passisok = true;

    do {
        std::system("clear");
        if (!passisok) {

            if (passctr == 0)
                throw std::invalid_argument("You Consumed your possibilites ");

            std::cout << "Password or Passport number do not match \n"
                      << "You have " << passctr << " times to try\n";
            passctr--;
        }
        passisok = false;
        std::cout << "Please enter your passport number\n";
        std::cin >> passnum;
        std::cout << "Enter your password\n";
        std::cin >> password;
    } while (j[passnum]["Password"] != password);

    for (json::iterator i = j.begin(); i != j.end(); i++) {

        if (i.key() == passnum) {

            int pcounter = 0;
            for (json::iterator k = i->begin(); k != i->end(); k++) {
                if (k.key() == "Password" || k.key() == "Transactions"
                    || k.key() == "Deposit")
                    continue;
                std::cout << pcounter + 1 << " " << k.key() << " " << k.value() << "\n";

                pcounter++;
            }

            std::cout << "Which paragraph do you want to change ?"
                         "\nOr enter 0 to exit\n";

            std::string value;
            int paragraph;
            std::cin >> paragraph;

            if (paragraph == 0)
                exit(1);

            paragraph--;
            pcounter = 0;

            for (json::iterator k = i->begin(); k != i->end(); k++) {

                if (k.key() == "Password" || k.key() == "Transactions"
                    || k.key() == "Deposit")
                    continue;
                if (paragraph == pcounter) {

                    std::cout << "Enter new value for " << k.key() << "\n";
                    std::cin.ignore();
                    getline(std::cin, value);
                    k.value() = value;
                }
                pcounter++;
            }

            std::system("clear");
            std::cout << "Your account updated successesfully !!\n\n\n";

            for (json::iterator k = i->begin(); k != i->end(); k++) {
                if (k.key() == "Password" || k.key() == "Transactions"
                    || k.key() == "Deposit")
                    continue;
                std::cout << k.key() << " " << k.value() << "\n";
            }
            std::cout << "\n\n";
        }

        std::ofstream out;
        out.open(path, std::ios::out);
        if (!out.is_open()) {
            std::cout << "Cannot open file\n";
            exit(1);
        }

        out << j.dump(4) << "\n";
        out.close();
    }
}

void Bank::transactions()
{

    std::ifstream fin;

    fin.open("bankfile.json");
    if (!fin.is_open()) {
        std::cout << "Cannot open file\n";
        exit(1);
    }

    json j;
    fin >> j;
    std::string passnum, password;

    int passctr = 3;
    bool passisok = true;

    do {
        std::system("clear");
        if (!passisok) {

            if (passctr == 0)
                throw std::invalid_argument("You Consumed your possibilites ");

            std::cout << "Password or Passport number do not match \n"
                      << "You have " << passctr << " times to try\n";
            passctr--;
        }
        passisok = false;

        std::cout << "Please enter your passport number\n";
        std::cin >> passnum;
        std::cout << "Enter your password\n";
        std::cin >> password;

    } while (j[passnum]["Password"] != password);

    int wantto;
    std::system("clear");
    std::cout << "1 If you want to withdraw money \n"
              << "2 If you want to add money \n";

    std::cin >> wantto;

    if (wantto == 1) {
        int money = j[passnum]["Deposit"];
        int amount;
        bool Isnumber;

        if (money > 0) {
            std::system("clear");
            std::cout << "Enter the amount\n";

            do {
                Isnumber = true;

                try {
                    std::cin >> amount;
                    if (std::cin.fail()) {
                        throw std::invalid_argument("Please input numbers only \n");
                    }
                } catch (std::exception& ex) {
                    std::cin.clear();
                    std::cin.ignore();
                    std::system("clear");
                    std::cout << ex.what();
                    Isnumber = false;
                }
            } while (!Isnumber);

            money = money - amount;
            j[passnum]["Deposit"] = money;
            j[passnum]["Transactions"].push_back(-amount);

            fin.close();
            std::ofstream out;
            out.open(path, std::ios::out);
            if (!out.is_open()) {
                std::cout << "Cannot open file\n";
                exit(1);
            }

            out << j.dump(4) << "\n";

            out.close();
        } else {
            std::system("clear");
            std::cout << "There is not enogh money on your account\n";
        }
    }
    if (wantto == 2) {
        int money = j[passnum]["Deposit"];

        int amount;
        bool Isnumber;

        std::system("clear");
        std::cout << "Enter the amount\n";

        do {

            Isnumber = true;

            try {
                std::cin >> amount;
                if (std::cin.fail())
                    throw std::invalid_argument("Please input numbers only \n");

            } catch (std::exception& ex) {
                std::cin.clear();
                std::cin.ignore();
                std::system("clear");
                std::cout << ex.what() << "\n";
                Isnumber = false;
            }
        } while (!Isnumber);

        money = money + amount;
        j[passnum]["Deposit"] = money;
        j[passnum]["Transactions"].push_back(amount);

        fin.close();
        std::ofstream out;
        out.open(path, std::ios::out);
        if (!out.is_open()) {
            std::cout << "Cannot open file\n";
            exit(1);
        }

        out << j.dump(4) << "\n";

        out.close();
    }
    if (fin.is_open())
        fin.close();
}

void ::Bank::check_det_acount()
{
    std::ifstream fin;

    fin.open("bankfile.json");
    if (!fin.is_open()) {
        std::cout << "Cannot open file\n";
        exit(1);
    }

    json j;
    fin >> j;

    std::string passnum, password;

    int passctr = 3;
    bool passisok = true;

    do {
        std::system("clear");
        if (!passisok) {

            if (passctr == 0)
                throw std::invalid_argument("You Consumed your possibilites ");

            std::cout << "Password or Passport number do not match \n"
                      << "You have " << passctr << " times to try\n";
            passctr--;
        }

        passisok = false;
        std::cout << "Please enter your passport number\n";
        std::cin >> passnum;
        std::cout << "Enter your password\n";
        std::cin >> password;

    } while (j[passnum]["Password"] != password);

    std::cout << "Your Deposit " << j[passnum]["Deposit"] << "\n\n";

    for (json::iterator tr = j[passnum]["Transactions"].begin();
         tr != j[passnum]["Transactions"].end(); tr++) {
        if (tr.value() > 0) {
            std::cout << "Add +" << tr.value() << "\n";
        } else if (tr.value() < 0) {
            std::cout << "Withdraw " << tr.value() << "\n";
        }
    }
    fin.close();
}

void Bank::rm_exs_account()
{

    std::ifstream fin;

    fin.open("bankfile.json");
    if (!fin.is_open()) {
        std::cout << "Cannot open file\n";
        exit(1);
    }

    json j;
    fin >> j;
    fin.close();
    std::string passnum, password;

    int passctr = 3;
    bool passisok = true;

    do {
        std::system("clear");
        if (!passisok) {

            if (passctr == 0)
                throw std::invalid_argument("You Consumed your possibilites ");

            std::cout << "Password or Passport number do not match \n"
                      << "You have " << passctr << " times to try\n";
            passctr--;
        }
        passisok = false;
        std::cout << "Please enter your passport number\n";
        std::cin >> passnum;
        std::cout << "Enter your password\n";
        std::cin >> password;

    } while (j[passnum]["Password"] != password);

    j.erase(passnum);
    std::ofstream out;
    out.open(path, std::ios::out);
    if (!out.is_open()) {
        std::cout << "Cannot open file \n";
        exit(1);
    }
    out << j.dump(4) << "\n";
    out.close();
}

void Bank::view_cust_list()
{
    std::ifstream fin;

    fin.open("bankfile.json");
    if (!fin.is_open()) {
        std::cout << "Cannot open file\n";
        exit(1);
    }

    json j;
    fin >> j;
    fin.close();
    std::string password, password2 = "0000";

    int passctr = 3;
    bool passisok = true;
    do {
        std::system("clear");
        if (!passisok) {

            if (passctr == 0)
                throw std::invalid_argument("You Consumed your possibilites ");

            std::cout << "Wrong password \n"
                      << "You have " << passctr << " times to try\n";
            passctr--;
        }
        passisok = false;
        std::cout << "Enter password\n";
        std::cin >> password;

    } while (password2 != password);

    for (json::iterator it = j.begin(); it != j.end(); it++) {
        for (json::iterator k = it->begin(); k != it->end(); k++) {
            std::cout << k.key() << " " << k.value() << "\n";
        }
        std::cout << "\n";
    }
}

