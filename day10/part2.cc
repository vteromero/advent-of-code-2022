#include <iostream>
#include <sstream>
#include <string>

using namespace std;

bool is_visible(int sprite, int cycle)
{
  int x = cycle % 40;
  return x >= sprite - 1 && x <= sprite + 1;
}

string next_pixel(int sprite, int cycle)
{
  if (is_visible(sprite, cycle)) {
    return "#";
  } else {
    return ".";
  }
}

int main()
{
  int sprite = 1;
  int cycle = 0;
  string crt;

  for (string line; getline(cin, line); ) {
    string inst;
    int v = 0;
    istringstream ss(line);

    ss >> inst >> v;

    if (inst == "addx") {
      crt += next_pixel(sprite, cycle) + next_pixel(sprite, cycle + 1);
      cycle += 2;
      sprite += v;
    } else if (inst == "noop") {
      crt += next_pixel(sprite, cycle);
      cycle += 1;
    }
  }

  cout <<
    crt.substr(0, 40) << endl <<
    crt.substr(40, 40) << endl <<
    crt.substr(80, 40) << endl <<
    crt.substr(120, 40) << endl <<
    crt.substr(160, 40) << endl <<
    crt.substr(200, 40) << endl;

  return 0;
}
