// FUNCTIONS TO ADD TO MAIN.CPP

// Want to include feature in the script that will be make it easy to manipulate all events!

vector<Event> saved_events;



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