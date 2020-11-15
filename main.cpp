#include "json.hpp"
#include <fstream>
#include <iostream>
using json = nlohmann::json;

int main()
{

    json j;
    std::ofstream out("myfile.json");

    j["val"] = "123";
    j["name"] = "Anna";

    if (out.is_open()) {
        out << j;
    } else {
        std::cout << "Err with opening  file!\n";
    }

    out.close();

    return 0;
}
