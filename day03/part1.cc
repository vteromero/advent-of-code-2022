#include <iostream>
#include <string>

using namespace std;

char find_common(string s1, string s2)
{
  for (size_t i = 0; i < s1.size(); i++) {
    if (s2.find(s1[i]) != string::npos) {
      return s1[i];
    }
  }
  return 0;
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
  int total = 0;

  for (string line; getline(cin, line); ) {
    string s1 = line.substr(0, line.size() / 2);
    string s2 = line.substr(line.size() / 2);
    total += priority(find_common(s1, s2));
  }

  cout << total << endl;

  return 0;
}
