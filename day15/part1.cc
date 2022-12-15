#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

//const int TARGET_Y = 10; // exmaple1.txt
const int TARGET_Y = 2000000; // input.txt

int dist(int x0, int y0, int x1, int y1)
{
  return abs(x0 - x1) + abs(y0 - y1);
}

bool cmp_segments(const pair<int, int> &a, const pair<int, int> &b)
{
  return a.first < b.first;
}

bool intersect(const pair<int, int> &a, const pair<int, int> &b)
{
  return b.first >= a.first && b.first <= a.second;
}

pair<int, int> merge(const pair<int, int> &a, const pair<int, int> &b)
{
  return make_pair(min(a.first, b.first), max(a.second, b.second));
}

vector<pair<int, int> > merge_segments(vector<pair<int, int> > &segments)
{
  vector<pair<int, int> > result;

  sort(segments.begin(), segments.end(), cmp_segments);

  result.push_back(segments[0]);

  for (size_t i=1, j=0; i < segments.size(); i++) {
    if (intersect(result[j], segments[i])) {
      result[j] = merge(result[j], segments[i]);
    } else {
      result.push_back(segments[i]);
      j++;
    }
  }

  return result;
}

bool segments_contain(const vector<pair<int, int> > &segments, int v)
{
  for (size_t i = 0; i < segments.size(); i++) {
    if (v >= segments[i].first && v <= segments[i].second) {
      return true;
    }
  }

  return false;
}

int main()
{
  vector<pair<int, int> > segments;
  set<pair<int, int> > beacon_set;

  for (string line; getline(cin, line); ) {
    int sx, sy, bx, by;

    sscanf(
      line.c_str(),
      "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d",
      &sx, &sy, &bx, &by
    );

    int d = dist(sx, sy, bx, by);
    int dtarget = abs(sy - TARGET_Y);

    if (d >= dtarget) {
      int diff = d - dtarget;
      segments.push_back(make_pair(sx - diff, sx + diff));
    }

    beacon_set.insert(make_pair(bx, by));
  }

  segments = merge_segments(segments);
  /*cout << "segments:" << endl;
  for (size_t i = 0; i < segments.size(); i++) {
    cout << segments[i].first << " - " << segments[i].second << endl;
  }*/

  int total = 0;
  for (size_t i = 0; i < segments.size(); i++) {
    total += segments[i].second - segments[i].first + 1;
  }

  /*cout << "beacons:" << endl;
  for (auto it = beacon_set.begin(); it != beacon_set.end(); it++) {
    cout << it->first << "," << it->second << endl;
  }*/
  for (auto it = beacon_set.begin(); it != beacon_set.end(); it++) {
    int x = it->first;
    int y = it->second;
    total -= y == TARGET_Y && segments_contain(segments, x);
  }

  cout << total << endl;

  return 0;
}
