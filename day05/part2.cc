#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

void read_stack_lines(vector<string> &lines)
{
  for (string line; getline(cin, line); ) {
    if (line.empty()) {
      break;
    }
    lines.push_back(line);
  }

  lines.pop_back();
}

void create_stacks(
  const vector<string> &stack_lines,
  vector<stack<char> > &stacks)
{
  for (size_t i = stack_lines.size(); i-- > 0; ) {
    for (size_t j = 0; j < stacks.size(); j++) {
      size_t pos = j * 4 + 1;
      char crate = stack_lines[i][pos];

      if (crate >= 'A' && crate <= 'Z') {
        stacks[j].push(crate);
      }
    }
  }
}

void read_and_run_instructions(vector<stack<char> > &stacks)
{
  for (string line; getline(cin, line); ) {
    string s1, s2, s3;
    int moves, from, to;
    istringstream ss(line);

    ss >> s1 >> moves >> s2 >> from >> s3 >> to;
    from--;
    to--;

    stack<char> temp;
    while (moves--) {
      temp.push(stacks[from].top());
      stacks[from].pop();
    }

    while (!temp.empty()) {
      stacks[to].push(temp.top());
      temp.pop();
    }
  }
}

void print_top_of_stacks(const vector<stack<char> > &stacks)
{
  for (size_t i = 0; i < stacks.size(); i++) {
    if (!stacks[i].empty()) {
      cout << stacks[i].top();
    }
  }
  cout << endl;
}

int main()
{
  vector<string> stack_lines;

  read_stack_lines(stack_lines);

  size_t num_stacks = (stack_lines[0].size() + 1) / 4;
  vector<stack<char> > stacks(num_stacks);

  create_stacks(stack_lines, stacks);

  read_and_run_instructions(stacks);

  print_top_of_stacks(stacks);

  return 0;
}
