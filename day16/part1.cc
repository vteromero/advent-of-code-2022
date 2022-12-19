#include <cstdlib>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct valve {
  int flow_rate;
  vector<size_t> adj_list;
};

vector<string> read_adj_tags(const string &line)
{
  size_t comma_pos = line.find(',');
  size_t pos = comma_pos == string::npos ? line.length() - 2 : comma_pos - 2;
  string adj_list_str = line.substr(pos);
  istringstream ss(adj_list_str);
  vector<string> list;

  for (string item; getline(ss, item, ','); ) {
    list.push_back(item.substr(item.length() - 2));
  }

  return list;
}

size_t add_tag(
  const string tag,
  vector<struct valve> &valves,
  map<string, size_t> &tag_to_index)
{
  if (tag_to_index.find(tag) == tag_to_index.end()) {
    tag_to_index[tag] = valves.size();
    valves.push_back((struct valve){});
  }
  return tag_to_index[tag];
}

vector<struct valve> read_graph()
{
  vector<struct valve> valves;
  map<string, size_t> tag_to_index;

  // we want 'AA' to be at position 0
  add_tag("AA", valves, tag_to_index);

  for (string line; getline(cin, line); ) {
    char buf[5];
    int flow_rate;

    sscanf(line.c_str(), "Valve %s has flow rate=%d;", buf, &flow_rate);

    string valve_tag(buf);
    size_t valve_idx = add_tag(valve_tag, valves, tag_to_index);

    vector<string> adj_tags = read_adj_tags(line);
    vector<size_t> adj_list;
    for (size_t i = 0; i < adj_tags.size(); i++) {
      adj_list.push_back(add_tag(adj_tags[i], valves, tag_to_index));
    }

    valves[valve_idx] = (struct valve){
      .flow_rate = flow_rate,
      .adj_list = adj_list
    };
  }
  /*cout << "tag_to_index:" << endl;
  for (auto it = tag_to_index.begin(); it != tag_to_index.end(); it++) {
    cout << it->first << ": " << it->second << endl;
  }
  cout << "valves:" << endl;
  for (size_t i = 0; i < valves.size(); i++) {
    cout << i <<
      ": flow_rate: " << valves[i].flow_rate <<
      ", adj_list:";
    for (size_t j = 0; j < valves[i].adj_list.size(); j++) {
      cout << " " << valves[i].adj_list[j];
    }
    cout << endl;
  }*/

  return valves;
}

vector<vector<int> > shortest_paths(const vector<struct valve> &valves)
{
  const size_t n = valves.size();
  const int inf = numeric_limits<int>::max();
  vector<vector<int> > dist(n, vector<int>(n, inf));

  for (size_t i = 0; i < n; i++) {
    dist[i][i] = 0;

    for (size_t j = 0; j < valves[i].adj_list.size(); j++) {
      dist[i][valves[i].adj_list[j]] = 1;
      dist[valves[i].adj_list[j]][i] = 1;
    }
  }

  for (size_t k = 0; k < n; k++) {
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < n; j++) {
        if (dist[i][k] == inf || dist[k][j] == inf) {
          continue;
        }
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
  /*cout << "dist:" << endl;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      cout << dist[i][j] << " ";
    }
    cout << endl;
  }*/

  return dist;
}

struct qitem {
  size_t    valve;        // current valve
  size_t    t;            // time in minutes
  int       flow_rate;    // current flow rate
  int       released;     // pressure released so far (up until t)
  uint64_t  open_valves;  // bit mask of open valves: 1 => open; 0 => closed
};

int main()
{
  vector<struct valve> valves = read_graph();
  vector<vector<int> > dist = shortest_paths(valves);
  queue<struct qitem> q;
  int most_pressure = 0;

  q.push((struct qitem){
    .valve = 0,
    .t = 0,
    .flow_rate = 0,
    .released = 0,
    .open_valves = 0
  });

  while (!q.empty()) {
    struct qitem item = q.front();
    q.pop();

    most_pressure = max(most_pressure, item.released + item.flow_rate * (int)(30 - item.t));

    for (size_t i = 0; i < valves.size(); i++) {
      if (item.open_valves & ((uint64_t)1 << i)) {
        continue;
      }

      if (valves[i].flow_rate == 0) {
        continue;
      }

      size_t t = item.t + dist[item.valve][i] + 1;
      int flow_rate = item.flow_rate + valves[i].flow_rate;
      int released = item.released + item.flow_rate * (dist[item.valve][i] + 1);
      uint64_t open_valves = item.open_valves | ((uint64_t)1 << i);

      if (t > 30) {
        continue;
      }

      q.push((struct qitem){
        .valve = i,
        .t = t,
        .flow_rate = flow_rate,
        .released = released,
        .open_valves = open_valves
      });
    }
  }

  cout << most_pressure << endl;

  return 0;
}
