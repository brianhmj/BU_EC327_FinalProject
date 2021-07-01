// Copyright 2021 Parker Dunn pgdunn@bu.edu
// Copyright 2021 Ben Gross bengee19@bu.edu
// Copyright 2021
// Copyright 2021

// Standard Libraries
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <math.h>

// SFML Libraries
#include <SFML/Graphics.hpp>

// Header file includes
#include "events.hpp"

// Includes features in this script:

/*
-- while loop controlling the application functions
     - display 7-day window
     - display 1-day window
     - display all appointments saved
     - allow entry of appointment information via the terminal (retreive from cin)

-- keep track of time in the while loop

-- if appoint is entered -> format it -> save to file (JSON)
      - month
      - day
      - year
      - appointment name
      - military time


*/

void show_day() {
  // this function will display a render window for events of a REQUESTED day
  sf::RenderWindow show_day(sf::VideoMode(1000, 1000), "group 5");
  std::string day_info,event_info,text_day,text_hour,text_minute,text_second;
  sf::Text time, event;
  sf::Font font;
  sf::RectangleShape border(sf::Vector2f(300,500));
  text_day = "1";//std::to_string(day);
  text_hour = "2";//std::to_string(hour);
  text_minute = "3";//std::to_string(minute);
  text_second = "4";//std::to_string(second);
  day_info =text_day+":"+text_hour+":"+text_minute+":"+text_second;//can be replaced with relevant fetch commands, remember what ever is fetch needs to be evtually converted into a string
  event_info ="hello" ;//grab this days logged event or the logged event of the specified day dont froget to convert it to string if nesscary 
  show_day.setFramerateLimit(1);
  border.setFillColor(sf::Color::Black);
  border.setOutlineColor(sf::Color::White);
  border.setOutlineThickness(1);
  border.setPosition(50,30);
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  time.setFont(font);
  time.setString(day_info);
  time.setPosition(50,30);
  event.setFont(font);
  event.setString(event_info);
  event.setPosition(50,60);
  while(show_day.isOpen()){
   show_day.clear();
   show_day.draw(border);
   show_day.draw(time);
   show_day.draw(event);
   show_day.display();
  }

}

void show_week() {
  // this function will display a render window with events for a REQUESTED week Sun - Sat

  // WINDOW SIZES

  // Setup a structure of using a couple render windows - FEEL FREE TO DELETE/CHANGE
  sf::RenderWindow show_week(sf::VideoMode(2000, 1000), "group 5");
  sf::Text d1,d2,d3,d4,d5,d6,d7,t1,t2,t3,t4,t5,t6,t7;
  sf::Font font;
  sf::RectangleShape day1(sf::Vector2f(200,300));
  sf::RectangleShape day2(sf::Vector2f(200,300));
  sf::RectangleShape day3(sf::Vector2f(200,300));
  sf::RectangleShape day4(sf::Vector2f(200,300));
  sf::RectangleShape day5(sf::Vector2f(200,300));
  sf::RectangleShape day6(sf::Vector2f(200,300));
  sf::RectangleShape day7(sf::Vector2f(200,300));

  show_week.setFramerateLimit(1);

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
  t1.setString("1:2:3:4");
  t2.setString("1:2:3:4");
  t3.setString("1:2:3:4");
  t4.setString("1:2:3:4");
  t5.setString("1:2:3:4");
  t6.setString("1:2:3:4");
  t7.setString("1:2:3:4");

  
  while(show_week.isOpen()){
  show_week.clear();
  show_week.draw(day1);
  show_week.draw(day2);
  show_week.draw(day3);
  show_week.draw(day4);
  show_week.draw(day5);
  show_week.draw(day6);
  show_week.draw(day7);
  show_week.draw(d1);
  show_week.draw(d2);
  show_week.draw(d3);
  show_week.draw(d4);
  show_week.draw(d5);
  show_week.draw(d6);
  show_week.draw(d7);
  show_week.draw(t1);
  show_week.draw(t2);
  show_week.draw(t3);
  show_week.draw(t4);
  show_week.draw(t5);
  show_week.draw(t6);
  show_week.draw(t7);
  show_week.display();
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
    std::cout << "enter a command: day, add, week, quit\n";
    std::cin >> command;
    if (command == "quit")
      break;
    else if (command == "day")
      show_day();
    else if (command == "add")
      saved_events.push_back(add_to_calendar());
    else if (command == "week")
      show_week();
    else
      std::cout << "command not understood\n";
  }


  return 0;
}