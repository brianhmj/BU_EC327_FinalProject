# Makes files for the project -- not tested or functional yet

all: calendar events

calendar: calendar.cpp
	g++ -g -std=c++20 calendar.cpp -o calendar -lsfml-graphics -lsfml-window -lsfml-system

events: events.hpp
	g++ -std=c++20 events.hpp -o events