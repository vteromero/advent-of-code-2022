#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const uint64_t DIR_MAX_SIZE = 100000;

void run_command(const string&, string&, map<string,uint64_t>&);

bool is_command(const string &line)
{
  return line[0] == '$';
}

string get_parent_path(const string &path)
{
  if (path == "/") {
    return "";
  } else {
    string parent = path.substr(0, path.find_last_of('/'));
    if (parent.empty()) {
      return "/";
    } else {
      return parent;
    }
  }
}

void run_cd(
  const string &path,
  string &current_path,
  map<string, uint64_t> &dir_size_map)
{
  if (path == "..") {
    current_path = get_parent_path(current_path);
  } else if (path[0] == '/' || current_path[current_path.length() - 1] == '/') {
    current_path += path;
  } else {
    current_path += "/" + path;
  }

  if (dir_size_map.find(current_path) == dir_size_map.end()) {
    dir_size_map[current_path] = 0;
  }
}

void update_tree_up(
  const string &path,
  uint64_t size,
  map<string, uint64_t> &dir_size_map)
{
  string p = path;

  while (!p.empty()) {
    dir_size_map[p] += size;
    p = get_parent_path(p);
  };
}

void run_ls(
  string &current_path,
  map<string, uint64_t> &dir_size_map)
{
  string line;
  uint64_t dir_size = 0;

  while (getline(cin, line) && !is_command(line)) {
    uint64_t size;
    istringstream ss(line);

    ss >> size;

    dir_size += size;
  }

  update_tree_up(current_path, dir_size, dir_size_map);

  if (is_command(line)) {
    run_command(line, current_path, dir_size_map);
  }
}

void run_command(
  const string &line,
  string &current_path,
  map<string, uint64_t> &dir_size_map)
{
  string prompt, command, param;
  istringstream ss(line);

  ss >> prompt >> command >> param;

  if (command == "cd") {
    run_cd(param, current_path, dir_size_map);
  } else if (command == "ls") {
    run_ls(current_path, dir_size_map);
  }
}

int main()
{
  string current_path("");
  map<string, uint64_t> dir_size_map;

  for (string line; getline(cin, line); ) {
    run_command(line, current_path, dir_size_map);
  }

  uint64_t total_sum = 0;
  for (auto it = dir_size_map.begin(); it != dir_size_map.end(); it++) {
    if (it->second <= DIR_MAX_SIZE) {
      total_sum += it->second;
    }
  }
  cout << total_sum << endl;

  return 0;
}
