// by J Carruthers for EC327

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "json.hpp"

using nlohmann::json;
using std::cout;

// generally, the top level of a C++ json object is a json-array or json-object,
// because these in turn can hold an arbitrary number of values, but it can be anything

int main()
{
    std::vector<std::string> json_filenames=
     {"first.json","second.json","third.json","fourth.json"};
     //,"xkcd_comics.json"};
    
    json j;
    std::ifstream jin;
    for (auto& fname : json_filenames) {
      cout << "--------" << fname << "--------\n";
      jin.open(fname);
      jin >> j;
      cout << j.dump(4) << '\n';
      jin.close();
    }

}
