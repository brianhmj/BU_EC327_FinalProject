# Makes files for the project -- not tested or functional yet

all: calendar events

all2: calendar2 events2

calendar: calendar.cpp
	g++ -g -std=c++20 calendar.cpp -o calendar -lsfml-graphics -lsfml-window -lsfml-system

events: events.hpp
	g++ -std=c++20 events.hpp -o events

calendar2: calendar2.cpp
	g++ -g -std=c++20 calendar2.cpp -o calendar2 -lsfml-graphics -lsfml-window -lsfml-system

events2: events2.hpp
	g++ -std=c++20 events2.hpp -o events2