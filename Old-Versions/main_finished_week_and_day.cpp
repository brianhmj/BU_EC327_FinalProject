// Copyright 2021 Parker Dunn pgdunn@bu.edu
// Copyright 2021 
// Copyright 2021
// Copyright 2021

// Standard Libraries
#include <iostream>
#include <ctime>
#include <chrono>
#include <cmath>
#include <cstring>
#include <vector>
#include <string>

// SFML Libraries
#include <SFML/Graphics.hpp>

// Header file includes


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

auto date(std::vector<int> date1, std::vector<int> date2){
    std::tm dur[2] {{0,0,0,date1[0],date1[1]-1,date1[2]-1900},{0,0,0,date2[0],date2[1]-1,date2[2]-1900}};
    std::time_t t1 {std::mktime(dur)}, t2 {std::mktime(dur+1)};
    if ( t1 != (std::time_t)(-1) && t2 != (std::time_t)(-1) ){
        return std::difftime(t2, t1);
    }else{
        return (double)INFINITY;
    }
}

void show_day() {

  int in_day;
  int in_month;
  int in_year;
  std::string command;
  int secAdjust = 0;

  std::vector<std::string> monthArray = {"Jan","Feb","March","April","May","June",
  "July","August","September","October","November","December"};

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


    sf::RenderWindow show_day(sf::VideoMode(1000, 1000), "group 5");
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
    event_info ="hello" ;//grab this days logged event or the logged event of the specified day dont froget to convert it to string if nesscary 
    show_day.setFramerateLimit(1);
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
    while(show_day.isOpen()){
     show_day.clear();
     show_day.draw(border);
     show_day.draw(time1);
     show_day.draw(event);
     show_day.display();

     while(show_day.pollEvent(Event)){
      if(Event.type == sf::Event::Closed){
          show_day.close();
      }
     }
    }

    //std::cout << "secAdjust is " << secAdjust << std::endl;

    // All this is just couts 
    // std::cout << asctime(localtime(&time)) << std::endl;
    // std::cout << year << std::endl;
    // std::cout << month << std::endl;
    // std::cout << day << std::endl;
    // std::cout << hour << std::endl;
    // std::cout << weekday << std::endl;
    // std::cout << minute << std::endl;
    // std::cout << second << std::endl;
    // std::cout << fulltime << std::endl;
    // std::cout << weekday << std::endl;

    std::vector<int> startday = {(int)day, (int)month, (int)year};
    std::vector<int> endday = {in_day,in_month,in_year};
    auto diff = date(startday,endday);
    // std::cout << diff << std::endl;

    std::cout << "Type new and hit enter for a new day, or enter quit to leave" << std::endl;
    std::cin >> command;
    if (command == "quit") {
      std::cout << "Going back to main program" << std::endl
      << "Enter a command: day, add, week, quit" << std::endl;
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

  std::vector<std::string> monthArray = {"Jan","Feb","March","April","May","June",
  "July","August","September","October","November","December"};

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
    t1.setString("Sun " + monthArray.at(int(theweek.at(0).tm_mon)) + " " + std::to_string((int)theweek.at(0).tm_mday));
    t2.setString("Mon " + monthArray.at(int(theweek.at(1).tm_mon)) + " " + std::to_string((int)theweek.at(1).tm_mday));
    t3.setString("Tue " + monthArray.at(int(theweek.at(2).tm_mon)) + " " + std::to_string((int)theweek.at(2).tm_mday));
    t4.setString("Wed " + monthArray.at(int(theweek.at(3).tm_mon)) + " " + std::to_string((int)theweek.at(3).tm_mday));
    t5.setString("Thu " + monthArray.at(int(theweek.at(4).tm_mon)) + " " + std::to_string((int)theweek.at(4).tm_mday));
    t6.setString("Fri " + monthArray.at(int(theweek.at(5).tm_mon)) + " " + std::to_string((int)theweek.at(5).tm_mday));
    t7.setString("Sat " + monthArray.at(int(theweek.at(6).tm_mon)) + " " + std::to_string((int)theweek.at(6).tm_mday));

    
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
      while(show_week.pollEvent(Event)){
        if(Event.type == sf::Event::Closed){
            show_week.close();
        }
      }
    }

    std::cout << "Type new and hit enter for a new week, or enter quit to leave" << std::endl;
    std::cin >> command;
    if (command == "quit") {
      std::cout << "Going back to main program" << std::endl
      << "Enter a command: day, add, week, quit" << std::endl;
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

void add_to_calendar() {

  // this function will add an event to your calendar

}


int main() {
  int argc;
  char** argv;

  std::string command;

  std::cout << "enter a command: day, add, week, quit\n";

  while (true) {
    std::cin >> command;
    if (command == "quit") {
      break;
    }
    else if (command == "day") {
      show_day();
    }
    else if (command == "add") {
      add_to_calendar();
    }
    else if (command == "week") {
      show_week();
    }
    else {
      std::cout << "command not understood" << std::endl;
    }
  }


  return 0;
}