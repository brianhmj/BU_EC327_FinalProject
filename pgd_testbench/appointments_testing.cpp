// Copyright 2021 Parker Dunn

#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <string>
#include <vector>

#include "json.hpp"
using nlohmann::json;

// using json = nlohmann::json;
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
  void save(); // will use this method to save appointment info to a json file
  void save_notification();

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

void Event::save() {

  json new_saved_event = 
  {
    {"name", this->name},
    {"month", this->date.at(0)},
    {"day", this->date.at(1)},
    {"year", this->date.at(2)},
    {
      "start time", start_time
    },
    {
      "end time", end_time
    },
    {"notify", this->notify}
  };

  // if (new_saved_event["notify"]) {
  //   (*this).save_notification();
  // }


  // need to save the json info now as a json file
  
  std::cout << new_saved_event.dump(2) << "\n"; // testing if you can see json data first

}

void Event::save_notification() {

  string notification_day;
  int notify_day;
  bool valid_notification = true;

  do {
    std::cout << "How many days before the event/appointment would you like to be notified?";
    std::cin >> notification_day;

    try {
      notify_day = std::stoi(notification_day);
    } catch (std::invalid_argument) {
      valid_notification = false;
      std::cout << "please enter an integer for the number of days.";
    }

    if (notify_day < 0) {
      valid_notification = false;
      std::cout << "Please enter a positive integer for the number of days.";
    }
  } while (!valid_notification);


  std::cout << "Here is what was entered for notification day: " << notify_day << "\n";

  // Now I would adjust the timing of the notification!
  // For now, I'm just setting up what the save structure.

  json new_notify = 
  {
    {"event name", this->name},
    {"event date", this->date},
    {"event time", this->start_time},
    {"notification_date", notification_day}, // this would probably hold more useful info
    {"notification_time", this->start_time}  // just holding start time is too limiting
  };

  // save the json file to computer with next set of lines!

  std::cout << new_notify.dump(4) << "\n"; // testing if you can see json data first

}

int main() {

  Event event1;
  
  event1.save();
  event1.save_notification();



  return 0;
}