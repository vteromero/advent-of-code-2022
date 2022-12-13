#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct qitem {
  int r;
  int c;
  int steps;
};

const int dr[] = {-1, 0, 0, 1};
const int dc[] = {0, -1, 1, 0};

int elevation(char c) {
  if (c == 'S') {
    c = 'a';
  } else if (c == 'E') {
    c = 'z';
  }
  return c - 'a';
}

int main()
{
  vector<string> grid;

  for (string line; getline(cin, line); ) {
    grid.push_back(line);
  }

  int rows = grid.size();
  int columns = grid[0].length();
  int sr=0, sc=0, er=0, ec=0;

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < columns; j++) {
      if (grid[i][j] == 'S') {
        sr = i;
        sc = j;
      } else if (grid[i][j] == 'E') {
        er = i;
        ec = j;
      }
    }
  }

  vector<vector<bool> > visited(rows, vector<bool>(columns, false));
  queue<qitem> q;

  q.push((struct qitem){sr, sc, 0});
  visited[sr][sc] = true;

  while (!q.empty()) {
    struct qitem item = q.front();
    q.pop();

    if (item.r == er && item.c == ec) {
      cout << item.steps << endl;
    } else {
      for (size_t i = 0; i < 4; i++) {
        int r = item.r + dr[i];
        int c = item.c + dc[i];

        if (r < 0 || r >= rows || c < 0 || c >= columns) {
          continue;
        }

        if (visited[r][c]) {
          continue;
        }

        int elev0 = elevation(grid[item.r][item.c]);
        int elev1 = elevation(grid[r][c]);

        if (elev1 - elev0 > 1) {
          continue;
        }

        q.push((struct qitem){r, c, item.steps + 1});
        visited[r][c] = true;
      }
    }
  }

  return 0;
}
