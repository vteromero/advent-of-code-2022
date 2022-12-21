#include <cstdlib>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

enum dir {xy = 0, xz = 1, yz = 2};

void add_to_set(set<vector<int> > &s, const vector<int> &v)
{
  if (s.find(v) == s.end()) {
    s.insert(v);
  } else {
    s.erase(v);
  }
}

int main()
{
  set<vector<int> > sides_set;

  for (string line; getline(cin, line); ) {
    int x, y, z;

    sscanf(line.c_str(), "%d,%d,%d", &x, &y, &z);

    vector<int> s1 = {x, y, z, xy};
    vector<int> s2 = {x, y, z + 1, xy};
    vector<int> s3 = {x, y, z, xz};
    vector<int> s4 = {x, y + 1, z, xz};
    vector<int> s5 = {x, y, z, yz};
    vector<int> s6 = {x + 1, y, z, yz};

    add_to_set(sides_set, s1);
    add_to_set(sides_set, s2);
    add_to_set(sides_set, s3);
    add_to_set(sides_set, s4);
    add_to_set(sides_set, s5);
    add_to_set(sides_set, s6);
  }

  cout << sides_set.size() << endl;

  return 0;
}
