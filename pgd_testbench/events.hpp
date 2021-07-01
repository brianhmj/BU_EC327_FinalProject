// USAGE INSTRUCTIONS

/*
Event constructors - 2 options
 (1) Event(name, month, day, year, description, notify)
  
  - This is the one that should most likely be used from main
  - Contents of event
    -- NAME - string - describes the event
    -- MONTH - int - saves the month
    -- DAY - int - saves the day
    -- YEAR - int - saves the year
    -- DESCRIPTION - string - just an opportunity to enter a longer string to describe the event
    -- NOTIFY - bool - if I get around to it this will store whether or not a notification window 
                       is supposed to be generated on the day of an event
 
 (2) Event(json)

  - this constructor re-creates events from files when they are stored as json files while the application is closed.


HOW FILE NAMES ARE CREATED: 

-- type_of_file + name of event + day + month + year + ".json" --- e.g. event_wedding_3062021.json

-- for "type of file" everything will typically be saved as "event"


*/


#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <string>
#include <vector>

#include "json.hpp"
using nlohmann::json;

using std::string;



void show_events(const vector<Event>* events) {
  for (auto e : events)
    std::cout << e.show() << "\n";
}

string date_to_display(int month, int day, int year) {

  typedef std::pair<int, string> MonthPair;
  map<MonthPair> months;
  months.emplace(MonthPair{1,"Jan"});
  months.emplace(MonthPair{2,"Feb"});
  months.emplace(MonthPair{3,"Mar"});
  months.emplace(MonthPair{4,"Apr"});
  months.emplace(MonthPair{5,"May"});
  months.emplace(MonthPair{6,"Jun"});
  months.emplace(MonthPair{7,"Jul"});
  months.emplace(MonthPair{8,"Aug"});
  months.emplace(MonthPair{9,"Sept"});
  months.emplace(MonthPair{10,"Oct"});
  months.emplace(MonthPair{11,"Nov"});
  months.emplace(MonthPair{12,"Dec"});

  return (months.at(month) + std::to_string(day) + std::to_string(year));
}

vector<Event> load_events(fs::path* AppData_Events, vector<Event>* saved_events, string name, int age) {

  for (auto& p : fs::directory_iterator("AppData/Events")) {
    json event;
    std::ifstream event_file(p.path());
    event_file >> event;
    event_file.close();

    saved_events->push_back(event)
  }
  return saved_events;
}

Event* find_event(const vector<Event>* saved, string find_name) {
  for (Event& e : *saved) {
    if (e.name == find_name) return &e;
  }
  return nullptr;
}


class Event {

  string name;
  bool notify;
  int month;
  int day;
  int year;
  string description;
  string filename;
  // std::vector<int> date;  // int month, day, and year
  // std::vector<int> start_time;  // int hours, minutes
  // std::vector<int> end_time;

public:
  // constructor to create new event
  Event(string in_name, int in_month, int in_day, int in_year, string in_description, bool in_notify = false) {
    name = in_name;
    month = in_month;
    day = in_day;
    year = in_year;
    description = in_description;
    notify = in_notify;
    filename = "event_" + name + std::to_string(day) + std::to_string(month) + std::to_string(year) + ".json";
  };

  // void new_event(); // not sure if I'll use this

  Event(json *j) {
    name = *j["name"];
    month = *j["month"];
    day = *j["day"];
    year = *j["year"];
    notify = *j["notify"];
    filename = *j["filename"];
  }
  
  string event_save(fs::path*); // will use this method to save appointment info to a json file
  void modify_event(vector<Event>*) {}; // modify/overwrite a json file already created
  void show(); // shows all stored events
  void delete_event(vector<Event>*); // want to be able to remove events when they have passed and been dismissed by user!

  // void notification() {};

};

string Event::show() {
  return "Name of event: " + name + " | " + date_to_display(month, day, year);
}

void Event::event_save(fs::path* AppData_Events) {

  // create json structure
  json new_saved_event = 
  {
    {"name", this->name},
    {"month", this->month},
    {"day", this->day},
    {"year", this->year},
    {"description", this->description};
    {"filename", this->filename},
    {"notify", this->notify};
  };

  // save to file
  fs::path save_file_loc = (*AppData_Events) / filename;
  std::ofstream jout{save_file_loc};
  jout << j << "\n";
  jout.close();
}

void modify_event(vector<Event>* saved) {
  string name_of_event;
  std::cout << "Here are the events you can choose from:\n\n";
  show_events(saved);
  std::cout << "\n\nPlease enter the name of the event that you would like to modify.";

  do {
    std::cout << "Use the name as it is typed in the list above.\n";
    cin >> name_of_event;
    Event* mod_e = find_event(saved, name_of_event);
  } while (mod_e == nullptr)

  *mod_e = add_to_calender()
}

void delete_event(vector<Event>* saved, fs::path* AppData_Events) {
  string name_of_event;
  std::cout << "Here are the events you can choose from:\n\n"
  show_events(saved);
  std::cout << "\n\nPlease enter the name of the event that you would like to delete.";

  do {
    std::cout << "Use the name as it is typed in the list above.\n";
    cin >> name_of_event;
    Event* mod_e = find_event(saved, name_of_event);
  } while (mod_e == nullptr)

  for (int i = 0; i < saved->size(); i++) {
    if (saved->name == name_of_event) saved->erase(saved->begin() + i);
  }

  for (auto& p : fs::directory_iterator("AppData/Events")) {
    if (p.path() == mod_e->filename)
      std::cout << "\nEvent file deleted.\n";
  }

}