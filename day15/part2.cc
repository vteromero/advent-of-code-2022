#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

//const int MAX_SIZE = 20; // example1.txt
const int MAX_SIZE = 4000000; // input.txt

struct scover {
  int sx;
  int sy;
  int d;
};

struct segment {
  int from;
  int to;
};

bool segment_cmp(const struct segment &a, const struct segment &b)
{
  return a.from < b.from;
}

bool segment_intersect(const struct segment &a, const struct segment &b)
{
  // assumptions / notes:
  // 1. a.from <= b.from
  // 2. when segments are "touching", the beginnig of b (b.from)
  //    is exactly 1 unit greater than the end of a (a.to)
  return b.from >= a.from && (b.from - a.to) <= 1;
}

struct segment segment_merge(const struct segment &a, const struct segment &b)
{
  return (struct segment){
    .from = min(a.from, b.from),
    .to = max(a.to, b.to)
  };
}

int dist(int x0, int y0, int x1, int y1)
{
  return abs(x0 - x1) + abs(y0 - y1);
}

vector<struct segment> raw_segments_at(const vector<struct scover> &sensors, int y)
{
  vector<struct segment> segments;

  for (size_t i = 0; i < sensors.size(); i++) {
    int dy = abs(sensors[i].sy - y);

    if (sensors[i].d >= dy) {
      int diff = sensors[i].d - dy;
      int from = sensors[i].sx - diff;
      int to = sensors[i].sx + diff;

      if (from <= MAX_SIZE && to >= 0) {
        segments.push_back((struct segment){
          .from = max(from, 0),
          .to = min(to, MAX_SIZE)
        });
      }
    }
  }

  return segments;
}

vector<struct segment> normalise_segments(vector<struct segment> &segments)
{
  vector<struct segment> result;

  sort(segments.begin(), segments.end(), segment_cmp);

  result.push_back(segments[0]);

  for (size_t i=1; i < segments.size(); i++) {
    if(segment_intersect(result[result.size() - 1], segments[i])) {
      result[result.size() - 1] = segment_merge(result[result.size() - 1], segments[i]);
    } else {
      result.push_back(segments[i]);
    }
  }

  return result;
}

vector<struct segment> segments_at(const vector<struct scover> &sensors, int y)
{
  vector<struct segment> segments = raw_segments_at(sensors, y);
  return normalise_segments(segments);
}

int main()
{
  vector<struct scover> sensors;

  for (string line; getline(cin, line); ) {
    int sx, sy, bx, by;

    sscanf(
      line.c_str(),
      "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d",
      &sx, &sy, &bx, &by
    );

    sensors.push_back((struct scover){
      .sx = sx,
      .sy = sy,
      .d = dist(sx, sy, bx, by)
    });
  }

  for (int y = 0; y <= MAX_SIZE; y++) {
    vector<struct segment> segments = segments_at(sensors, y);
    /*cout << "y=" << y;
    for (size_t i = 0; i < segments.size(); i++) {
      cout << "  " << segments[i].from << " - " << segments[i].to;
    }
    cout << endl;*/

    if (segments.size() > 1) {
      int64_t x = segments[0].to + 1;
      int64_t freq = 4000000 * x + (int64_t)y;
      cout << "(" << x << "," << y << "), freq: " << freq << endl;
      break;
    }
  }

  return 0;
}
