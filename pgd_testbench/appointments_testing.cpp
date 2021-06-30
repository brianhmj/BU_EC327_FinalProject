// Copyright 2021 Parker Dunn

#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <string>
#include <vector>

#include "json/single_include/nlohmann/json.hpp"

using json = nlohmann::json;
using std::string;


class Event {

  string name;

  std::vector<int> date;  // int month, day, and year
  std::vector<int> start_time;  // int hours, minutes
  std::vector<int> end_time;

  bool notify;

public:

  Event(); // constructor to create new event - set to read all info about event in!

  // void new_event(); // not sure if I'll use this

  void save() {}; // will use this method to save appointment info to a json file

  void modify_event() {}; // modify/overwrite a json file already created

  void delete_event() {}; // want to be able to remove events when they have passed and been dismissed by user!

  void show_events() {}; // shows all stored events


  void notification() {};

};

Event::Event() {
  
  date.resize(3);
  start_time.resize(2);
  end_time.resize(2);
  std::vector<string> requests{"month", "day", "year",
                          "start hour", "start min",
                          "end hour", "end min"};
  std::cout << "Name of event: ";
  std::cin >> this->name;

  for (int i = 0; i < 3; i++) {
    std::cout << "enter " << requests.at(i) << ": ";
    std::cin >> this->date.at(i);
  }

  for (int i = 3; i < 5; i++) {
    std::cout << "enter " << requests.at(i) << ": ";
    std::cin >> this->start_time.at(i-3);
  }

  for (int i = 5; i < requests.size(); i++) {
    std::cout << "enter " << requests.at(i) << ": ";
    std::cin >> this->end_time.at(i-5); 
  }

  std::cout << "want notification? Enter 1 for true OR 0 for false. ";
  std::cin >> this->notify;
}



int main() {

  Event event1;

  return 0;
}