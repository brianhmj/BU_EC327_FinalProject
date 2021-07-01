# BU_EC327_FinalProject

Calendar app created with C++ as our final project for EC327 class.

## Contributors 

- Landon Kushimi lsk1801@bu.edu
- Parker Dunn pgdunn@bu.edu
- Ben Gross bengee19@bu.edu
- Homoon Jung brianhmj@bu.edu

## How to use the script

The program is dependent on three files included with the project:
(1) calendar.cpp - main program
(2) events.hpp   - contains functions and structures used for the application
(3) json.hpp     - data format used to save information

The three scripts must be in downloaded together and accessible to the primary script (calendar.cpp) for to generate an executable file.

An executable for the program can easily be created in Linux using the *make* command. You must have the three files noted above in the working directory along with the Makefile included with the project. Additionally, the SFML packages must be downloaded and available to *make* to compile the project. With this setup, the executale for the program can be creaed using the command below:

> *make all*

The Makefile for the project is designed to include the necessary dependencies automatically to make the compiling process easier.

There is curretly no setup for the script to be compiled on a Windows device. The linux platform via software like Ubuntu is needed to compile the scripts.

## Long Description

This repo contains all scripts and files related to the development and testing of a calendar application built using the Simple and Fast Multimedia Library ([SFML](https://wwww.sfml-dev.org/index.php)).

The core features of the application incldue:
(1) view events on a requested day or week
(2) add events/notifications to the calender and have the information saved
(3) remove and modify events after they have been created
(4) Review all events you have saved

The application saves all event information in json format in a subfolder called AppData of the directory where the program is run.
