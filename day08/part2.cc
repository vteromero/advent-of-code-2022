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
  vector<vector<int> > tree_score(rows, vector<int>(columns, 1));

  // from top
  for (int i = 0; i < columns; i++) {
    vector<int> last_pos(10, -1);

    for (int j = 0; j < rows; j++) {
      int h = tree_map[j][i] - '0';
      int pos = 0;

      for (int k = h; k < 10; k++) {
        pos = max(pos, last_pos[k]);
      }

      tree_score[j][i] *= j - pos;
      last_pos[h] = j;
    }
  }

  // from bottom
  for (int i = 0; i < columns; i++) {
    vector<int> last_pos(10, rows);

    for (int j = rows; j-- > 0; ) {
      int h = tree_map[j][i] - '0';
      int pos = rows - 1;

      for (int k = h; k < 10; k++) {
        pos = min(pos, last_pos[k]);
      }

      tree_score[j][i] *= pos - j;
      last_pos[h] = j;
    }
  }

  // from left
  for (size_t i = 0; i < rows; i++) {
    vector<int> last_pos(10, -1);

    for (size_t j = 0; j < columns; j++) {
      int h = tree_map[i][j] - '0';
      int pos = 0;

      for (int k = h; k < 10; k++) {
        pos = max(pos, last_pos[k]);
      }

      tree_score[i][j] *= j - pos;
      last_pos[h] = j;
    }
  }

  // from right
  for (size_t i = 0; i < rows; i++) {
    vector<int> last_pos(10, columns);

    for (size_t j = columns; j-- > 0; ) {
      int h = tree_map[i][j] - '0';
      int pos = columns - 1;

      for (int k = h; k < 10; k++) {
        pos = min(pos, last_pos[k]);
      }

      tree_score[i][j] *= pos - j;
      last_pos[h] = j;
    }
  }

  /*for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < columns; j++) {
      cout << tree_score[i][j] << " ";
    }
    cout << endl;
  }*/

  int highest_score = 0;

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < columns; j++) {
      highest_score = max(highest_score, tree_score[i][j]);
    }
  }

  cout << highest_score << endl;

  return 0;
}
