// Adapted from doc/examples/README.cpp
// by J Carruthers for EC327

#include <iostream>
#include <fstream>

#include "json.hpp"

using nlohmann::json;


// JSON values         C++ equivalent     Python Equivalent
//    object               map               dictionary
//    array/list           vector            list
//    string
//    number         
//    bool ("true" or "false")
//    null ("null")

int main()
{
    // create a JSON object
    // note that this is C++ syntax, so key/value pairs
    // are 
    // C++:   {"key",value},
    // json:  "key":value,

    json j =
    {
        {"pi", 3.141},
        {"happy", true},
        {"name", "Niels"},
        {"nothing", nullptr}, 
        {
            "answer", {
                {"everything", 42}
            }
        },
        {"list", {1, 0, 2}},
        {
            "object", {
                {"currency", "USD"},
                {"value", 42.99}
            }
        }
    };

    // add new values
    j["new"]["key"]["value"] = {"another", "list"};

    // count elements
    auto s = j.size();
    j["size"] = s;

    // pretty print with indent of 4 spaces
    std::cout <<  j.dump(4) << '\n';

    // normal print
    std::cout  << j << '\n';
    int i{9};
    // save the result to a file.
    std::ofstream jout{"second.cpp"};
    std::cin >> i;
    //return 0;
    jout << j << '\n';
    jout.close();

}
