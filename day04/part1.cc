#include <iostream>
#include <sstream>
#include <string>

using namespace std;

bool fully_contained(int a, int b, int c, int d)
{
  return (a >= c && b <= d) || (c >= a && d <= b);
}

int main()
{
  int count = 0;

  for (string line; getline(cin, line); ) {
    int a, b, c, d;
    char c1, c2, c3;
    istringstream ss(line);

    ss >> a >> c1 >> b >> c2 >> c >> c3 >> d;

    count += fully_contained(a, b, c, d);
  }

  cout << count << endl;

  return 0;
}
