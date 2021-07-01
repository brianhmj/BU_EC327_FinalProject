// Copyright 2021 Parker Dunn pgdunn@bu.edu
// Copyright 2021 Ben Gross bengee19@bu.edu
// Copyright 2021 Landon Kushimi lsh
// Copyright 2021 Homoon Jung (Brian) 

// Standard Libraries
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <math.h>
#include <cmath>
#include <cstring>

// SFML Libraries
#include <SFML/Graphics.hpp>

// Header file includes
#include "events.hpp"


auto date(std::vector<int> date1, std::vector<int> date2){
    std::tm dur[2] {{0,0,0,date1[0],date1[1]-1,date1[2]-1900},{0,0,0,date2[0],date2[1]-1,date2[2]-1900}};
    std::time_t t1 {std::mktime(dur)}, t2 {std::mktime(dur+1)};
    if ( t1 != (std::time_t)(-1) && t2 != (std::time_t)(-1) ){
        return std::difftime(t2, t1);
    }else{
        return (double)INFINITY;
    }
}



void show_day(vector<Event>* saved_events) {

  int in_day;
  int in_month;
  int in_year;
  std::string command;
  int secAdjust = 0;

  std::vector<std::string> monthArray = {"Jan","Feb","Mar","Apr","May","Jun",
  "Jul","Aug","Sep","Oct","Nov","Dec"};

  // if (argc > 2) {
  //   in_day = std::stoi(argv[1]);
  //   in_month = std::stoi(argv[2]);
  //   in_year = std::stoi(argv[3]);
  //   inputs = true;
  // }

  while(true) {

    std::time_t time = std::time(NULL) + secAdjust;
    std::tm now = *std::localtime(&time);


    float year = 1900 + now.tm_year;
    float month = now.tm_mon + 1;
    float day = now.tm_mday;
    float hour = now.tm_hour;
    float minute = now.tm_min;
    float second = now.tm_sec;
    std::string fulltime = asctime(localtime(&time));
    std::string weekday = fulltime.substr(0,3);


    sf::RenderWindow s_day(sf::VideoMode(1000, 1000), "group 5");
    std::string day_info,event_info,text_day,text_hour,text_minute,text_second,text_month,text_year;
    sf::Text time1, event;
    sf::Font font;
    sf::Event Event;
    sf::RectangleShape border(sf::Vector2f(300,500));
    text_day = weekday;//std::to_string(day);
    text_month = monthArray.at((int)month - 1);//std::to_string(hour);
    text_year = std::to_string((int)year);
    // text_second = std::to_string(second);
    day_info =text_day + " " + text_month + " " +
    std::to_string((int)day) + " " + text_year;//can be replaced with relevant fetch commands, remember what ever is fetch needs to be evtually converted into a string
    

    event_info = "";
    int temp_month = month, 
        temp_day = day,
        temp_year = year;

    for (auto ev : *saved_events) {
      vector<int> saved_date = ev.get_date();
      if (saved_date.at(0) == temp_month and saved_date.at(1) == temp_day and saved_date.at(2) == temp_year)
        event_info += ("\n" + ev.get_name() + "\n");
    }
    //grab this days logged event or the logged event of the specified day dont froget to convert it to string if nesscary 

    s_day.setFramerateLimit(10);
    border.setFillColor(sf::Color::Black);
    border.setOutlineColor(sf::Color::White);
    border.setOutlineThickness(1);
    border.setPosition(50,30);
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
    time1.setFont(font);
    time1.setString(day_info);
    time1.setPosition(50,30);
    event.setFont(font);
    event.setString(event_info);
    event.setPosition(50,60);
    while(s_day.isOpen()){
     s_day.clear();
     s_day.draw(border);
     s_day.draw(time1);
     s_day.draw(event);
     s_day.display();

     while(s_day.pollEvent(Event)){
      if(Event.type == sf::Event::Closed){
          s_day.close();
      }
     }
    }

    std::vector<int> startday = {(int)day, (int)month, (int)year};
    std::vector<int> endday = {in_day,in_month,in_year};
    auto diff = date(startday,endday);
    // std::cout << diff << std::endl;

    std::cout << "Type new and hit enter for a new day, or enter quit to leave" << std::endl;
    std::cin >> command;
    if (command == "quit") {
      std::cout << "Going back to main program" << std::endl;
      // << "Enter a command: day, add, week, quit" << std::endl;
      break;
    } else if (command == "new") {
        std::cout << "Enter a new day in day month year format" << std::endl;
        std::time_t timeNow = std::time(NULL);
        std::tm now2 = *std::localtime(&timeNow);
        std::cin >> in_day >> in_month >> in_year;
        // std::cout << in_day << in_month << in_year << std::endl;
        std::vector<int> startday = {(int)(now2.tm_mday), (int)(now2.tm_mon + 1), (int)(1900 + now2.tm_year)};
        // std::cout << now2.tm_mday << " " << now2.tm_mon + 1 << " " << now2.tm_year + 1900 << std::endl;
        std::vector<int> endday = {in_day,in_month,in_year};
        auto diff = date(startday,endday);
        //std::cout << diff << std::endl;
        secAdjust = diff;
        // bigSecAdjust = secAdjust + bigSecAdjust;
        // std::cout << "secAdjust is " << secAdjust << std::endl;
    } else {
        std::cout << "Command not understood" << std::endl;
    }
  }
}

void show_week() {
  int secAdjust = 0;
  std::string command;
  sf::Event Event;
  int in_day;
  int in_month;
  int in_year;
  int secDay = 86400;

  std::vector<std::string> monthArray = {"Jan","Feb","Mar","Apr","May","Jun",
  "Jul","Aug","Sep","Oct","Nov","Dec"};

  while (true) {
    std::time_t inputTime = std::time(NULL) + secAdjust;
    std::tm inputTm = *std::localtime(&inputTime);
    std::string weekin_fulltime = asctime(localtime(&inputTime));
    std::string weekin_weekday = weekin_fulltime.substr(0,3);
    std::vector<int> loopNum;
    std::tm wSunday = inputTm, wMonday = inputTm, wTuesday = inputTm,
     wWednesday = inputTm, wThursday = inputTm, wFriday= inputTm,
     wSaturday = inputTm;
    std::vector<std::tm> theweek = {wSunday, wMonday, wTuesday,
      wWednesday, wThursday, wFriday, wSaturday};

    if (weekin_weekday == "Sun") {
      loopNum = {0,6}; 
    } else if (weekin_weekday == "Mon") {
      loopNum = {1,5};
    } else if (weekin_weekday == "Tue") {
      loopNum = {2,4};
    } else if (weekin_weekday == "Wed") {
      loopNum = {3,3};
    } else if (weekin_weekday == "Thu") {
      loopNum = {4,2};
    } else if (weekin_weekday == "Fri") {
      loopNum = {5,1};
    } else if (weekin_weekday == "Sat") {
      loopNum = {6,0};
    } else {
      loopNum = {0,0};
    }
   
    int multiplier1 = 0;
    for (int i = loopNum.at(0); i < 7; i++) {
      inputTime = inputTime + (multiplier1 * secDay);
      multiplier1 += 1;
      theweek.at(i) = *std::localtime(&inputTime);
      inputTime = std::time(NULL) + secAdjust;
      // theweek.at(i).tm_mday += multiplier1;
    }

    int multiplier2 = 1;
    for (int j = 5-loopNum.at(1); j >= 0; j--) {
      inputTime = inputTime - (multiplier2 * secDay);
      theweek.at(j) = *std::localtime(&inputTime);
      multiplier2 += 1;
      inputTime = std::time(NULL) + secAdjust;
      // theweek.at(j).tm_mday -= multiplier2;
    }

    // std::cout << theweek.at(0).tm_mday << std::endl;
    // std::cout << theweek.at(1).tm_mday << std::endl;
    // std::cout << theweek.at(2).tm_mday << std::endl;
    // std::cout << theweek.at(3).tm_mday << std::endl;
    // std::cout << theweek.at(4).tm_mday << std::endl;
    // std::cout << theweek.at(5).tm_mday << std::endl;
    // std::cout << theweek.at(6).tm_mday << std::endl;


    sf::RenderWindow s_week(sf::VideoMode(2000, 1000), "group 5");
    sf::Text d1,d2,d3,d4,d5,d6,d7,t1,t2,t3,t4,t5,t6,t7;
    sf::Font font;
    sf::RectangleShape day1(sf::Vector2f(200,300));
    sf::RectangleShape day2(sf::Vector2f(200,300));
    sf::RectangleShape day3(sf::Vector2f(200,300));
    sf::RectangleShape day4(sf::Vector2f(200,300));
    sf::RectangleShape day5(sf::Vector2f(200,300));
    sf::RectangleShape day6(sf::Vector2f(200,300));
    sf::RectangleShape day7(sf::Vector2f(200,300));

    s_week.setFramerateLimit(10);

    day1.setFillColor(sf::Color::Black);
    day1.setOutlineColor(sf::Color::White);
    day1.setOutlineThickness(1);
    day2.setFillColor(sf::Color::Black);
    day2.setOutlineColor(sf::Color::White);
    day2.setOutlineThickness(1);
    day3.setFillColor(sf::Color::Black);
    day3.setOutlineColor(sf::Color::White);
    day3.setOutlineThickness(1);
    day4.setFillColor(sf::Color::Black);
    day4.setOutlineColor(sf::Color::White);
    day4.setOutlineThickness(1);
    day5.setFillColor(sf::Color::Black);
    day5.setOutlineColor(sf::Color::White);
    day5.setOutlineThickness(1);
    day6.setFillColor(sf::Color::Black);
    day6.setOutlineColor(sf::Color::White);
    day6.setOutlineThickness(1);
    day7.setFillColor(sf::Color::Black);
    day7.setOutlineColor(sf::Color::White);
    day7.setOutlineThickness(1);

    day1.setPosition(50,20);
    day2.setPosition(250,20);
    day3.setPosition(450,20);
    day4.setPosition(650,20);
    day5.setPosition(850,20);
    day6.setPosition(1050,20);
    day7.setPosition(1250,20);

    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
    d1.setFont(font);
    d2.setFont(font);
    d3.setFont(font);
    d4.setFont(font);
    d5.setFont(font);
    d6.setFont(font);
    d7.setFont(font);
    t1.setFont(font); 
    t2.setFont(font);
    t3.setFont(font);
    t4.setFont(font);
    t5.setFont(font);
    t6.setFont(font);
    t7.setFont(font);

    d1.setPosition(50,50);
    d2.setPosition(250,50); 
    d3.setPosition(450,50);
    d4.setPosition(650,50);
    d5.setPosition(850,50);
    d6.setPosition(1050,50);
    d7.setPosition(1250,50);
    t1.setPosition(50,20);
    t2.setPosition(250,20);
    t3.setPosition(450,20);
    t4.setPosition(650,20);
    t5.setPosition(850,20);
    t6.setPosition(1050,20);
    t7.setPosition(1250,20);

    d1.setFillColor(sf::Color::White);
    d2.setFillColor(sf::Color::White);
    d3.setFillColor(sf::Color::White);
    d4.setFillColor(sf::Color::White);
    d5.setFillColor(sf::Color::White);
    d6.setFillColor(sf::Color::White);
    d7.setFillColor(sf::Color::White);
    t1.setFillColor(sf::Color::White);
    t2.setFillColor(sf::Color::White);
    t3.setFillColor(sf::Color::White);
    t4.setFillColor(sf::Color::White);
    t5.setFillColor(sf::Color::White);
    t6.setFillColor(sf::Color::White);
    t7.setFillColor(sf::Color::White);

    d1.setString("hi");//info from json file goes here
    d2.setString("hi");
    d3.setString("hi");
    d4.setString("hi");
    d5.setString("hi");
    d6.setString("hi");
    d7.setString("hi");

    // vector<sf::Text> day

    t1.setString("Sun " + monthArray.at(int(theweek.at(0).tm_mon)) + " " + std::to_string((int)theweek.at(0).tm_mday));
    t2.setString("Mon " + monthArray.at(int(theweek.at(1).tm_mon)) + " " + std::to_string((int)theweek.at(1).tm_mday));
    t3.setString("Tue " + monthArray.at(int(theweek.at(2).tm_mon)) + " " + std::to_string((int)theweek.at(2).tm_mday));
    t4.setString("Wed " + monthArray.at(int(theweek.at(3).tm_mon)) + " " + std::to_string((int)theweek.at(3).tm_mday));
    t5.setString("Thu " + monthArray.at(int(theweek.at(4).tm_mon)) + " " + std::to_string((int)theweek.at(4).tm_mday));
    t6.setString("Fri " + monthArray.at(int(theweek.at(5).tm_mon)) + " " + std::to_string((int)theweek.at(5).tm_mday));
    t7.setString("Sat " + monthArray.at(int(theweek.at(6).tm_mon)) + " " + std::to_string((int)theweek.at(6).tm_mday));

    
    while(s_week.isOpen()){
      s_week.clear();
      s_week.draw(day1);
      s_week.draw(day2);
      s_week.draw(day3);
      s_week.draw(day4);
      s_week.draw(day5);
      s_week.draw(day6);
      s_week.draw(day7);
      s_week.draw(d1);
      s_week.draw(d2);
      s_week.draw(d3);
      s_week.draw(d4);
      s_week.draw(d5);
      s_week.draw(d6);
      s_week.draw(d7);
      s_week.draw(t1);
      s_week.draw(t2);
      s_week.draw(t3);
      s_week.draw(t4);
      s_week.draw(t5);
      s_week.draw(t6);
      s_week.draw(t7);
      s_week.display();
      while(s_week.pollEvent(Event)){
        if(Event.type == sf::Event::Closed){
            s_week.close();
        }
      }
    }

    std::cout << "Type new and hit enter for a new week, or enter quit to leave" << std::endl;
    std::cin >> command;
    if (command == "quit") {
      std::cout << "Going back to main program" << std::endl;
      // << "Enter a command: day, add, week, quit" << std::endl;
      break;
    } else if(command == "new") {
        std::cout << "Enter a day for which you want the week displayed" << std::endl;
        std::time_t timeNow = std::time(NULL);
        std::tm now2 = *std::localtime(&timeNow);
        std::cin >> in_day >> in_month >> in_year;
        // std::cout << in_day << in_month << in_year << std::endl;
        std::vector<int> startday = {(int)(now2.tm_mday), (int)(now2.tm_mon + 1), (int)(1900 + now2.tm_year)};
        // std::cout << now2.tm_mday << " " << now2.tm_mon + 1 << " " << now2.tm_year + 1900 << std::endl;
        std::vector<int> endday = {in_day,in_month,in_year};
        auto diff = date(startday,endday);
        //std::cout << diff << std::endl;
        secAdjust = diff;
        // bigSecAdjust = secAdjust + bigSecAdjust;
        // std::cout << "secAdjust is " << secAdjust << std::endl;
    } else {
        std::cout << "Command not understood" << std::endl;
    }

  }
}

int main() {

  std::string command;

  const fs::path WD = fs::current_path();
  const fs::path APPDATA = WD / "AppData";
  const fs::path APPDATA_EVENTS = APPDATA / "Events";

  fs::create_directory(APPDATA);
  fs::create_directory(APPDATA_EVENTS);


  vector<Event> saved_events = load_events(&APPDATA_EVENTS);


  while (true) {
    std::cout << "\nEnter a command for the application:\n\n"
              << "\tEnter 'day' to view specific days from the calendar\n"
              << "\tEnter 'week' to view an entire week from the calendar\n"
              << "\tEnter 'add' to add an event to the calendar\n"
              << "\tEnter 'events' to view all events you have saved\n"
              << "\tEnter 'quit' if you would like to exit the application\n";


    std::cin >> command;
    if (command == "quit")
      break;
    else if (command == "day")
      show_day(&saved_events);
    else if (command == "add") {
      Event e = add_to_calendar();
      e.event_save(&APPDATA_EVENTS);
      saved_events.push_back(e);
    } else if (command == "week") {
      show_week();
    } else if (command == "events") {
      std::cout << "\n\nHere are all the events currently saved in your calendar:\n\n";
      show_events(&saved_events);
    } else
      std::cout << "command not understood\n";
  }

  return 0;
}