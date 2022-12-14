#include <cassert>
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

pair<int, int> calculate_vertical_limits(
  const vector<vector<pair<int, int> > > &paths)
{
  pair<int, int> lim_y = make_pair(numeric_limits<int>::max(),
                                   numeric_limits<int>::min());

  for (size_t i = 0; i < paths.size(); i++) {
    for (size_t j = 0; j < paths[i].size(); j++) {
      int y = paths[i][j].second;
      lim_y.first = min(lim_y.first, y);
      lim_y.second = max(lim_y.second, y);
    }
  }

  lim_y.first = min(lim_y.first, START_Y);
  lim_y.second = max(lim_y.second, START_Y);

  return lim_y;
}

vector<string> create_grid(
  const vector<vector<pair<int, int> > > &paths,
  const pair<int, int> &lim_x,
  const pair<int, int> &lim_y,
  int rows,
  int columns)
{
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
          grid[y - lim_y.first][from_x - lim_x.first] = '#';
        }
      } else if (from_y == to_y) {
        int from = min(from_x, to_x);
        int to = max(from_x, to_x);
        for (int x = from; x <= to; x++) {
          grid[from_y - lim_y.first][x - lim_x.first] = '#';
        }
      }

      from_x = to_x;
      from_y = to_y;
    }
  }

  return grid;
}

void print_grid(const vector<string> &grid)
{
  for (size_t i = 0; i < grid.size(); i++) {
    for (size_t j = 0; j < grid[i].size(); j++) {
      cout << grid[i][j];
    }
    cout << endl;
  }
}

pair<int, int> fall(
  int x,
  int y,
  const vector<string> &grid,
  int rows,
  int columns)
{
  assert(x >= 0 && x < columns);
  assert(y >= 0 && y < rows);

  if (y == rows - 1) {
    return make_pair(x, y);
  }

  if (grid[y + 1][x] == '.') {
    return fall(x, y + 1, grid, rows, columns);
  } else if (grid[y + 1][x - 1] == '.') {
    return fall(x - 1, y + 1, grid, rows, columns);
  } else if (grid[y + 1][x + 1] == '.') {
    return fall(x + 1, y + 1, grid, rows, columns);
  }

  return make_pair(x, y);
}

size_t count_char(char c, const vector<string> &grid)
{
  size_t total = 0;

  for (size_t i = 0; i < grid.size(); i++) {
    for (size_t j = 0; j < grid[i].size(); j++) {
      total += grid[i][j] == c;
    }
  }

  return total;
}

int main()
{
  vector<vector<pair<int, int> > > paths;

  for (string line; getline(cin, line); ) {
    paths.push_back(read_path(line));
  }

  pair<int, int> lim_y = calculate_vertical_limits(paths);
  lim_y.second++; // add a row
  int rows = lim_y.second - lim_y.first + 1;
  pair<int, int> lim_x = make_pair(START_X - rows, START_X + rows);
  int columns = lim_x.second - lim_x.first + 1;
  //cout << "lim x: " << lim_x.first << ", " << lim_x.second << endl;
  //cout << "lim y: " << lim_y.first << ", " << lim_y.second << endl;
  //cout << "rows: " << rows << ", columns: " << columns << endl;

  vector<string> grid = create_grid(paths, lim_x, lim_y, rows, columns);
  //print_grid(grid);

  int start_x = START_X - lim_x.first;

  while (1) {
    auto pos = fall(start_x, 0, grid, rows, columns);
    grid[pos.second][pos.first] = 'o';
    if (pos.first == start_x && pos.second == 0) {
      break;
    }
  };
  //cout << endl;
  //print_grid(grid);

  cout << count_char('o', grid) << endl;

  return 0;
}
