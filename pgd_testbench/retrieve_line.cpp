#include <iostream>
#include <fstream>
#include <string>




int main() {

  std::string read_in;

  // std::cin >> read_in;
  std::getline(std::cin, read_in);

  std::cout << read_in << "\n";

  return 0;
}