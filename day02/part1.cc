#include <iostream>

using namespace std;

int score(char c0, char c1)
{
  int i = c0 - 'A';
  int j = c1 - 'X';
  const int outcome[3][3] = {
    {1+3, 2+6, 3+0},
    {1+0, 2+3, 3+6},
    {1+6, 2+0, 3+3}
  };

  return outcome[i][j];
}

int main()
{
  int total = 0;

  for (char opponent, you; cin >> opponent >> you; ) {
    total += score(opponent, you);
  }

  cout << total << endl;

  return 0;
}
