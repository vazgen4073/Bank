#include "bank.h"

Bank::Bank()
{
}

void Bank::create_account()
{
    json j;
    Person ps;
    out.open("bankfile.json", std::ios::app);

    if (!out.is_open()) {
        std::cout << "Cannot open file!\n";
        exit(1);
    }

    std::cout << "Please enter your name \n";
    std::cin >> ps.name;
    std::cout << "Please enter your last name \n";
    std::cin >> ps.last_name;
    std::cout << "Please enter your middle name \n";
    std::cin >> ps.middle_name;
    std::cout << "Please enter your passport number \n";
    std::cin >> ps.passport_number;
    std::cin.ignore();
    std::cout << "Please enter your date of birth \n";
    getline(std::cin, ps.date_of_birth);
    std::cout << "Please enter your deposit \n";
    std::cin >> ps.money;

    account_number++;

    std::string staccount_number = ps.passport_number;

    j[ps.passport_number] = {
        { " Name", ps.name },
        { " Middle Name", ps.middle_name },
        { " Last Name", ps.last_name },
        { " Date of birth", ps.date_of_birth },
        { " Deposit", ps.money }
    };

    out << j.dump(4);

    out.close();

    std::cout << "Your account created successesfully !\n";
}

void Bank::update_inf_exs_account()
{

    std::fstream finout;
    finout.open("bankfile.json", std::fstream::in | std::fstream::out);

    std::ofstream temp;
    temp.open("temp.json"); //delete file
    temp.close(); //

    temp.open("temp.json", std::ios::app);

    if (!finout) {
        std::cout << "Cannot open file!\n";
        exit(1);
    }

    if (!temp) {
        std::cout << "Cannot open file!\n";
        exit(1);
    }

    json j;

    std::string passnum;

    std::cout << "Please enter your passport number\n";
    std::cin >> passnum;

    bool isend = false;
    while (!finout.eof()) { //ete aranc try catch-i em
        //  grum  chi  ashxatum

        //  terminate called after throwing an instance of
        // 'nlohmann::detail::parse_error'  what():
        // [json.exception.parse_error.101] parse error
        // at line 1, column 1:  syntax error while parsing
        // value - unexpected end of input; expected '[', '{', or a literal

        try {
            finout >> j;
        } catch (std::exception& ex) {
            isend = true;
        }

        if (isend)
            break;

        for (json::iterator i = j.begin(); i != j.end(); i++) {

            if (i.key() == passnum) {

                int pcounter = 0;

                for (json::iterator k = i->begin(); k != i->end(); k++) { //print details

                    std::cout << pcounter + 1 << " " << k.key() << " " << k.value() << "\n";

                    pcounter++;
                }

                std::cout << "Which paragraph do you want to change ?"
                             "\nPlease enter it \n";

                std::string value;
                int paragraph;

                std::cin >> paragraph;
                paragraph--;
                pcounter = 0;

                for (json::iterator k = i->begin(); k != i->end(); k++) {

                    if (paragraph == pcounter) {

                        std::cout << "Enter new value for " << k.key() << "\n";
                        std::cin.ignore();
                        getline(std::cin, value);
                        k.value() = value;
                    }
                    pcounter++;
                }

                std::cout << "Your account updated successesfully !!\n\n\n";

                for (json::iterator k = i->begin(); k != i->end(); k++) { //print details
                    std::cout << k.key() << " " << k.value() << "\n";
                }

                std::cout << "\n\n";
            }
            temp << j.dump(4);
        }

        j.clear();
    }

    temp.close();
    finout.close();
    std::ifstream temp2;

    finout.open("bankfile.json", std::ios::out | std::ios::trunc);
    temp2.open("temp.json");

    if (!finout.is_open() || !temp2.is_open()) {
        std::cout << "Cannot open file\n";
        exit(1);
    }

    json j2;

    isend = false;

    while (1) { //copy from temp file to main file

        if (isend)
            break;

        try {
            temp2 >> j2;
            finout << j2.dump(4);

        } catch (std::exception& ex) {
            isend = true;
        }
    }

    temp2.close();
    finout.close();
}
