#include <iostream>
#include <sstream>
#include <string>

using namespace std;

bool overlap(int a, int b, int c, int d)
{
  return (a >= c && a <= d) || (c >= a && c <= b);
}

int main()
{
  int count = 0;

  for (string line; getline(cin, line); ) {
    int a, b, c, d;
    char c1, c2, c3;
    istringstream ss(line);

    ss >> a >> c1 >> b >> c2 >> c >> c3 >> d;

    count += overlap(a, b, c, d);
  }

  cout << count << endl;

  return 0;
}
