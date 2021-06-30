// Adapted from doc/examples/README.cpp
// by J Carruthers for EC327

#include <iostream>
#include <vector>

#include "json.hpp"

using nlohmann::json;
using std::cout;
using std::vector;

struct Card {
  bool special;
  int n;
} ;


void to_json(json& j, const Card& p) {
    j = json{{"special", p.special}, {"n", p.n}};
}

void from_json(const json& j, Card& p) {
    j.at("special").get_to(p.special);
    j.at("n").get_to(p.n);
 }

int main()
{
    Card mycard{false,1};
    json j = mycard;

    cout << j << '\n';

    j["special"]=true;
    Card anothercard = j;
    json k = anothercard;
    cout << k << "\n";

    vector<Card> v{{false,1},{false,2}};

    json hand = v;
    cout << hand << "\n";

}
