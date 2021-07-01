// Copyright 2021 Parker Dunn

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <string>
#include <vector>

#include "json.hpp"
using nlohmann::json;

namespace fs = std::filesystem;

// using json = nlohmann::json;
using std::string;


string first_word(string name) {
  for (int i = 0; i < name.size(); i++) {
    if (name.at(i) == ' ') return name.substr(0,i);
  }
  return name;
}

void save_json(json* j, fs::path* AppData) {

  int age = j->at("age");

  string filename = first_word(j->at("name")) + std::to_string(age) + ".json";
  fs::path save_file_loc = (*AppData) / filename;

  std::ofstream jout{save_file_loc};
  jout << j << "\n";
  jout.close();

}

json load_json(fs::path* AppData, string name, int age) {

  json event;
  string file = name + std::to_string(age) + ".json";
  bool found = false;

  string find = "AppData/" + file;

  for (auto& p : fs::directory_iterator("AppData")) {
    std::cout << p.path() << "\n";
    if (p.path() == find) {
      std::ifstream event_file(p.path());
      event_file.open();
      event_file >> event;
      event_file.close();
      found = true;
    }
    if (found) break;
  }
  // fs::filesystem_error er("ERROR: Did not find event you requested.", *AppData);
  // json::other_error er("Event not found");
  if (!found) std::cout << "ERROR: Did not find event you requested.\n";

  return event;
}



int main() {

  const fs::path wd = fs::current_path();
  fs::path AppData = wd / "AppData";

  std::cout << "\nCurrent path is " << wd << "\n";

  std::cout << "\nThe path where AppData could go " << AppData << "\n\n";

  json j = {
    {"name", "Josh Fuller"},
    {"age", 24}
  };


  save_json(&j, &AppData);

  json j2 = load_json(&AppData, "Josh", 24);

  std::cout << j2.dump(3) << "\n";


  return 0;
}