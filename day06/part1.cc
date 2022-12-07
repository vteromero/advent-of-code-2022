#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

const int MARKER_LEN = 4;

int main()
{
  vector<int> last_occur('z' - 'a' + 1, numeric_limits<int>::min());
  int goal = MARKER_LEN - 1;
  string line;

  getline(cin, line);

  for (int i = 0; i < line.length(); i++) {
    int dist = i - last_occur[line[i]];

    last_occur[line[i]] = i;

    if (dist < MARKER_LEN) {
      goal = max(goal, i + MARKER_LEN - dist);
    }

    if (goal == i) {
      cout << (i + 1) << endl;
      return 0;
    }
  }

  cout << "Not found!" << endl;

  return 0;
}
