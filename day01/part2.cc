#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
  vector<int> calories(1, 0);

  for (string item; getline(cin, item); ) {
    if (item.empty()) {
      calories.push_back(0);
    } else {
      calories[calories.size() - 1] += stoi(item);
    }
  }

  sort(calories.begin(), calories.end(), greater<int>());

  cout << calories[0] + calories[1] + calories[2] << endl;

  return 0;
}
