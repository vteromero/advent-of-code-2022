#include <iostream>
#include <limits>
#include <string>

using namespace std;

int main()
{
  int max_cal = numeric_limits<int>::min();
  int cal = 0;

  for (string item; getline(cin, item); ) {
    if (item.empty()) {
      max_cal = max(max_cal, cal);
      cal = 0;
    } else {
      cal += stoi(item);
    }
  }

  cout << max_cal << endl;

  return 0;
}
