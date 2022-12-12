#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>

using namespace std;

struct pos {
  int x;
  int y;
};

void update_tail(
  const struct pos &h,
  struct pos &t)
{
  if (t.y == h.y + 2) {
    t.y--;
    t.x = h.x;
  } else if (t.y == h.y - 2) {
    t.y++;
    t.x = h.x;
  } else if (t.x == h.x + 2) {
    t.x--;
    t.y = h.y;
  } else if (t.x == h.x - 2) {
    t.x++;
    t.y = h.y;
  }
}

string pos_to_string(const struct pos &p)
{
  ostringstream ss;

  ss << p.x << "," << p.y;

  return ss.str();
}

int main()
{
  struct pos h = {0, 0};
  struct pos t = {0, 0};
  unordered_set<string> t_pos_set;

  t_pos_set.insert(pos_to_string(t));

  for (string line; getline(cin, line); ) {
    char dir;
    int steps;
    istringstream ss(line);

    ss >> dir >> steps;

    for (int i = 1; i <= steps; i++) {
      switch (dir) {
        case 'U':
          h.y++;
          break;
        case 'D':
          h.y--;
          break;
        case 'L':
          h.x--;
          break;
        case 'R':
          h.x++;
          break;
      }

      update_tail(h, t);

      t_pos_set.insert(pos_to_string(t));
    }
  }

  cout << t_pos_set.size() << endl;

  return 0;
}
