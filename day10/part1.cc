#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
  int x = 1;
  size_t cycles = 1;
  size_t target[] = {20, 60, 100, 140, 180, 220};
  size_t target_sz = sizeof(target) / sizeof(target[0]);
  size_t i = 0;
  int strength_sum = 0;

  for (string line; getline(cin, line); ) {
    string inst;
    int v = 0;
    istringstream ss(line);

    ss >> inst >> v;

    if (inst == "addx") {
      cycles += 2;
      x += v;
    } else if (inst == "noop") {
      cycles += 1;
    }

    if (i < target_sz && cycles > target[i]) {
      strength_sum += target[i] * (x - v);
      i++;
    }
  }

  cout << strength_sum << endl;

  return 0;
}
