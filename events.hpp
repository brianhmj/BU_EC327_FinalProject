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
#include <fstream>
#include <filesystem>
#include <map>
#include <string>
#include <vector>

#include "json.hpp"
using nlohmann::json;

namespace fs = std::filesystem;

using std::string;
using std::map;
using std::vector;
using std::cin;

typedef std::pair<int, string> MonthPair;


string date_to_display(int month, int day, int year) {
  map<int, string> months;
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

  return (months.at(month) + " " + std::to_string(day) + " " + std::to_string(year));
}

class Event {

  string name;
  bool notify;
  int month;
  int day;
  int year;
  string description;
  string filename;

public:
  // constructor to create new event
  Event(string in_name, string in_month, string in_day, string in_year, string in_description, bool in_notify = false) {
    name = in_name;
    month = std::stoi(in_month);
    day = std::stoi(in_day);
    year = std::stoi(in_year);
    description = in_description;
    notify = in_notify;

    filename = "event_";
    for (char c : name) {
      if (c == ' ') filename += '-';
      else filename += c;
    }
    filename += std::to_string(day) + std::to_string(month) + std::to_string(year);
    for (int i = 0; i < 5; i++) {
      if (description.at(i) == ' ') filename += '-';
      else filename += description.at(i);
    }
    filename += ".json";
  }

  Event(string in_name, int in_month, int in_day, int in_year, string in_description, bool in_notify = false) {
    name = in_name;
    month = in_month;
    day = in_day;
    year = in_year;
    description = in_description;
    notify = in_notify;

    filename = "event_";
    for (char c : name) {
      if (c == ' ') filename += '-';
      else filename += c;
    }
    filename += std::to_string(day) + std::to_string(month) + std::to_string(year);
    for (int i = 0; i < 5; i++) {
      if (description.at(i) == ' ') filename += '-';
      else filename += description.at(i);
    }
    filename += ".json";
  }

  Event(json* j) {
    name = j->at("name");
    month = j->at("month");
    day = j->at("day");
    year = j->at("year");
    notify = j->at("notify");
    filename = j->at("filename");
    description = j->at("description");
  }
  
  void event_save(const fs::path*); // will use this method to save appointment info to a json file
  void delete_event(vector<Event>*, const fs::path*); // want to be able to remove events when they have passed and been dismissed by user!
  string show(); // shows all stored events
  string get_name() {
    return this->name;
  }
  string get_filename() {
    return this->filename;
  }
  vector<int> get_date() {
    vector<int> date{this->month, this->day, this->year};
    return date;
  }
  string get_description() {
    return this->description;
  }

  // void notification() {};

};

Event add_to_calendar() {
  // this function will add an event to your calendar
  std::string name, month, day, year, description, temp_name;
  std::cout << "\nname of event: ";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::getline(std::cin, name);
  std::cout << "Month (entered as ##, ex. febuary is 02)" << std::endl;
  std::cin >> month;
  std::cout << "Day (entered as ##, ex. twenty first day is 21)" << std::endl;
  std::cin >> day;
  std::cout << "Year (entered as ####, ex. for the year twenty twenty one enter 2021)" << std::endl;
  std::cin >> year;
  std::cout << "event description\n";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::getline(std::cin, description);
  Event e(name,month,day,year,description);
  return e;
}

void show_events(vector<Event>* events) {
  for (auto& e : *events)
    std::cout << e.show() << "\n";
}

Event* find_event(vector<Event>* saved, string find_name) {
  for (Event& e : *saved) {
    if (e.get_name() == find_name) return &e;
  }
  return nullptr;
}

string Event::show() {
  return "Event Name: " + name + " - Date: " + date_to_display(month, day, year) 
                        + " - " + description.substr(0,10) + "...";
}

void Event::event_save(const fs::path* APPDATA_EVENTS) {

  // create json structure
  json new_saved_event = 
  {
    {"name", this->name},
    {"month", this->month},
    {"day", this->day},
    {"year", this->year},
    {"description", this->description},
    {"filename", this->filename},
    {"notify", this->notify}
  };

  // save to file
  fs::path save_file_loc = (*APPDATA_EVENTS) / filename;
  std::ofstream jout{save_file_loc};
  jout << new_saved_event << "\n";
  jout.close();
}

Event* modify_event(vector<Event>* saved) {
  string name_of_event;
  Event* mod_e;
  std::cout << "Here are the events you can choose from:\n\n";
  show_events(saved);
  std::cout << "\n\nPlease enter the name of the event that you would like to modify.";

  do {
    std::cout << "Use the name as it is typed in the list above.\n";
    cin >> name_of_event;
    mod_e = find_event(saved, name_of_event);
  } while (mod_e == nullptr);

  for (auto& p : fs::directory_iterator("AppData/Events")) {
    if (p.path() == ("AppData/Events/" + mod_e->get_filename())) {
      bool success = fs::remove(p.path());
    }
  }

  *mod_e = add_to_calendar();
  return mod_e;
}

void delete_event(vector<Event>* saved, const fs::path* APPDATA_EVENTS) {
  string name_of_event;
  Event* mod_e;
  std::cout << "Here are the events you can choose from:\n\n";
  show_events(saved);
  std::cout << "\n\nPlease enter the name of the event that you would like to delete.\n";

  do {
    std::cout << "Use the name as it is typed in the list above.\n";
    cin >> name_of_event;
    mod_e = find_event(saved, name_of_event);
  } while (mod_e == nullptr);

  for (auto& p : fs::directory_iterator("AppData/Events")) {
    if (p.path() == ("AppData/Events/" + mod_e->get_filename())) {
      bool success = fs::remove(p.path());
      if (success) std::cout << "\nEvent file deleted.\n";
    }
  }

  for (int i = 0; i < saved->size(); i++) {
    if ((saved->at(i)).get_name() == name_of_event) saved->erase(saved->begin() + i);
  }

}

vector<Event> load_events(const fs::path* APPDATA_EVENTS) {
  vector<Event> saved_events;
  for (auto& p : fs::directory_iterator("AppData/Events")) {
    json event;
    std::ifstream event_file(p.path());
    event_file >> event;
    event_file.close();

    Event e(&event);

    saved_events.push_back(e);
  }
  return saved_events;
}