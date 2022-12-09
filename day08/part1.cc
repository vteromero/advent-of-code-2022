#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
  vector<string> tree_map;

  for (string line; getline(cin, line); ) {
    tree_map.push_back(line);
  }

  size_t rows = tree_map.size();
  size_t columns = tree_map[0].size();
  vector<vector<bool> > tree_visible(rows, vector<bool>(columns, false));

  // from top
  for (size_t i = 0; i < columns; i++) {
    int max_h = -1;
    for (size_t j = 0; j < rows; j++) {
      int h = tree_map[j][i] - '0';
      if (h > max_h) {
        tree_visible[j][i] = true;
        max_h = h;
      }
    }
  }

  // from bottom
  for (size_t i = 0; i < columns; i++) {
    int max_h = -1;
    for (size_t j = rows; j-- > 0; ) {
      int h = tree_map[j][i] - '0';
      if (h > max_h) {
        tree_visible[j][i] = true;
        max_h = h;
      }
    }
  }

  // from left
  for (size_t i = 0; i < rows; i++) {
    int max_h = -1;
    for (size_t j = 0; j < columns; j++) {
      int h = tree_map[i][j] - '0';
      if (h > max_h) {
        tree_visible[i][j] = true;
        max_h = h;
      }
    }
  }

  // from right
  for (size_t i = 0; i < rows; i++) {
    int max_h = -1;
    for (size_t j = columns; j-- > 0; ) {
      int h = tree_map[i][j] - '0';
      if (h > max_h) {
        tree_visible[i][j] = true;
        max_h = h;
      }
    }
  }

  /*for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < columns; j++) {
      cout << tree_visible[i][j];
    }
    cout << endl;
  }*/

  size_t total = 0;

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < columns; j++) {
      total += tree_visible[i][j];
    }
  }

  cout << total << endl;

  return 0;
}
