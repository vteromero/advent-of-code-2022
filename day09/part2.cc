#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

struct pos {
  int x;
  int y;
};

void update_knot(
  const struct pos &prev,
  struct pos &cur)
{
  const int dy[5][5] = {
    {-1, -1, -1, -1, -1},
    {-1,  0,  0,  0, -1},
    { 0,  0,  0,  0,  0},
    { 1,  0,  0,  0,  1},
    { 1,  1,  1,  1,  1}
  };
  const int dx[5][5] = {
    { 1,  1,  0, -1, -1},
    { 1,  0,  0,  0, -1},
    { 1,  0,  0,  0, -1},
    { 1,  0,  0,  0, -1},
    { 1,  1,  0, -1, -1}
  };
  int x = cur.x - prev.x + 2;
  int y = prev.y - cur.y + 2;

  cur.x += dx[y][x];
  cur.y += dy[y][x];
}

void update_knots(vector<struct pos> &knots)
{
  for (size_t i = 1; i < knots.size(); i++) {
    update_knot(knots[i - 1], knots[i]);
  }
}

void print_knots(const vector<struct pos> &knots)
{
  for (size_t i = 0; i < knots.size(); i++) {
    cout << "(" << knots[i].x << "," << knots[i].y << ") ";
  }
  cout << endl;
}

string pos_to_string(const struct pos &p)
{
  ostringstream ss;
  ss << p.x << "," << p.y;
  return ss.str();
}

int main()
{
  vector<struct pos> knots(10, (struct pos){0, 0});
  unordered_set<string> tail_pos_set;

  tail_pos_set.insert(pos_to_string(knots[9]));
  //print_knots(knots);

  for (string line; getline(cin, line); ) {
    char dir;
    int steps;
    istringstream ss(line);

    //cout << line << endl;
    ss >> dir >> steps;

    for (int i = 1; i <= steps; i++) {
      switch (dir) {
        case 'U':
          knots[0].y++;
          break;
        case 'D':
          knots[0].y--;
          break;
        case 'L':
          knots[0].x--;
          break;
        case 'R':
          knots[0].x++;
          break;
      }

      update_knots(knots);
      //print_knots(knots);

      tail_pos_set.insert(pos_to_string(knots[9]));
    }
  }

  cout << tail_pos_set.size() << endl;

  return 0;
}
