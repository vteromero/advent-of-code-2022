#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string unique_chars(const string &s)
{
  string out;

  for (size_t i = 0; i < s.size(); i++) {
    if (out.find(s[i]) == string::npos) {
      out.append(1, s[i]);
    }
  }

  return out;
}

string common_chars(const string &s1, const string &s2)
{
  string out;

  for (size_t i = 0; i < s1.size(); i++) {
    if (s2.find(s1[i]) != string::npos) {
      out.append(1, s1[i]);
    }
  }

  return out;
}

char find_common(const vector<string> &group)
{
  string common = unique_chars(group[0]);

  for (size_t i = 1; i < group.size(); i++) {
    common = common_chars(common, unique_chars(group[i]));
  }

  return common[0];
}

int priority(char c)
{
  if (c >= 'a' && c <= 'z') {
    return c - 'a' + 1;
  } else {
    return c - 'A' + 27;
  }
}

int main()
{
  vector<string> group;
  int total = 0;

  for (string line; getline(cin, line); ) {
    group.push_back(line);

    if (group.size() == 3) {
      total += priority(find_common(group));
      group.clear();
    }
  }

  cout << total << endl;

  return 0;
}
