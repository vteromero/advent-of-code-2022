#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const int START_X = 500;
const int START_Y = 0;

vector<pair<int, int> > read_path(const string &line)
{
  vector<pair<int, int> > path;
  char comma;
  int a, b;
  string arrow;
  istringstream ss(line);

  ss >> a >> comma >> b;
  path.push_back(make_pair(a, b));

  while (ss >> arrow >> a >> comma >> b) {
    path.push_back(make_pair(a, b));
  }

  return path;
}

bool is_free_falling(int x, int y, int rows, int columns)
{
  return x == 0 || x == columns - 1 || y == rows - 1;
}

pair<int, int> fall(int x, int y, const vector<string> &grid)
{
  int rows = grid.size();
  int columns = grid[0].size();

  if (is_free_falling(x, y, rows, columns)) {
    return make_pair(x, y);
  }

  if (grid[y + 1][x] == '.') {
    return fall(x, y + 1, grid);
  } else if (grid[y + 1][x - 1] == '.') {
    return fall(x - 1, y + 1, grid);
  } else if (grid[y + 1][x + 1] == '.') {
    return fall(x + 1, y + 1, grid);
  }

  return make_pair(x, y);
}

int main()
{
  vector<vector<pair<int, int> > > paths;

  for (string line; getline(cin, line); ) {
    paths.push_back(read_path(line));
  }

  int min_x = numeric_limits<int>::max();
  int max_x = numeric_limits<int>::min();
  int min_y = numeric_limits<int>::max();
  int max_y = numeric_limits<int>::min();

  for (size_t i = 0; i < paths.size(); i++) {
    for (size_t j = 0; j < paths[i].size(); j++) {
      int x = paths[i][j].first;
      int y = paths[i][j].second;

      min_x = min(min_x, x);
      max_x = max(max_x, x);
      min_y = min(min_y, y);
      max_y = max(max_y, y);
    }
  }

  min_x = min(min_x, START_X);
  max_x = max(max_x, START_X);
  min_y = min(min_y, START_Y);
  max_y = max(max_y, START_Y);
  //cout << min_x << "," << max_x << endl;
  //cout << min_y << "," << max_y << endl;

  int rows = max_y - min_y + 1;
  int columns = max_x - min_x + 1;
  //cout << "rows: " << rows << ", columns: " << columns << endl;
  int start_x = START_X - min_x;
  //cout << "start_x: " << start_x << endl;
  vector<string> grid(rows, string(columns, '.'));

  for (size_t i = 0; i < paths.size(); i++) {
    int from_x = paths[i][0].first;
    int from_y = paths[i][0].second;

    for (size_t j = 1; j < paths[i].size(); j++) {
      int to_x = paths[i][j].first;
      int to_y = paths[i][j].second;

      if (from_x == to_x) {
        int from = min(from_y, to_y);
        int to = max(from_y, to_y);
        for (int y = from; y <= to; y++) {
          grid[y - min_y][from_x - min_x] = '#';
        }
      } else if (from_y == to_y) {
        int from = min(from_x, to_x);
        int to = max(from_x, to_x);
        for (int x = from; x <= to; x++) {
          grid[from_y - min_y][x - min_x] = '#';
        }
      }

      from_x = to_x;
      from_y = to_y;
    }
  }
  /*for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < columns; j++) {
      cout << grid[i][j];
    }
    cout << endl;
  }*/

  while (1) {
    auto pos = fall(start_x, 0, grid);
    if (is_free_falling(pos.first, pos.second, rows, columns)) {
      break;
    }
    grid[pos.second][pos.first] = 'o';
  };
  /*cout << endl;
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < columns; j++) {
      cout << grid[i][j];
    }
    cout << endl;
  }*/

  size_t total = 0;

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < columns; j++) {
      total += grid[i][j] == 'o';
    }
  }

  cout << total << endl;

  return 0;
}
