# Makes files for the project -- not tested or functional yet

all: main

main: main.cpp
	g++ -g -std=c++20 main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system