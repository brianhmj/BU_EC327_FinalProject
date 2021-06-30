// Copyright 2021 Parker Dunn pgdunn@bu.edu
// Copyright 2021 
// Copyright 2021
// Copyright 2021

// Standard Libraries
#include <iostream>
#include <chrono>
#include <ctime>
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

void show_day() {
  // this function will display a render window for events of a REQUESTED day

}

void show_week() {
  // this function will display a render window with events for a REQUESTED week Sun - Sat

  // WINDOW SIZES
  unsigned int width = 700;
  unsigned int height = 200;

  // Setup a structure of using a couple render windows - FEEL FREE TO DELETE/CHANGE
  sf::RenderWindow seven_days(sf::VideoMode(seven_width, seven_height))

  // got distracted and didn't finish yet - feel free to delete this and update

}

void add_to_calendar() {

  // this function will add an event to your calendar

}


int main() {

  string command;

  cout << "enter a command: show day, add, show week, quit\n";

  while (true) {
    std::cin >> command;
    if (command == "quit")
      break;
    else if (command == "show day")
      show_day();
    else if (command == "add")
      add_to_calendar();
    else if (command == "show week")
      show_week();
    else
      cout << "command not understood";
  }


  return 0;
}