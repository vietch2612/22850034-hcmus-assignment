// Among the many juicy stone fruits in Vietnam, mangoes are one of the most
// commonly eaten fruits. Ti also has a mango tree in his backyard and this is
// an eccentric tree without leaves and totally flattened!!! There is only one
// root branch grown up from the trunk of the tree and from that branch has the
// most two other branches up, they are the same but one up to the lefe and one
// to the right. The branches continue to expand
// higher with one or two more grown up from it.
// On each branch we have a mango and each
// mango has its own value. The value of a mango
// on the right branch is always larger than the
// mango on its origin, and is smaller or equal for
// the mango on the left (see picture).
// One morning, Ti came to his tree and tried to
// count the mangoes on the tree. From Ti standing
// spot - right to the bottom of the tree, the
// mangoes in the higher positions might be covered by the others in lower.
// Since the tree is tall and there are many mangoes on it, he could not follow
// all of them. Now, he wants you to help him, how many mangoes can he count
// from the bottom of the tree? Input The input consists of two lines. The first
// line is a positive integer n (1 <= n <= 1.000.000), - the number of mangoes.
// The second line is a sequence of n positive integers, each separates by a
// space - the value of mangoes. The value of mangos is listed by their
// positions. From the lower to higher and from the left to right. Output Print
// in one line the list of value of mangoes that can be observed in ascending
// order. Sample input and output:
// Input
// 8
// 2 1 6 5 8 4 7 3
// Output:
// 1 2 3 6 8
// Input
// 6
// 1 5 3 4 3 5
// Output
// 1 3 5 5

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  stack<int> s;
  s.push(a[0]);
  for (int i = 1; i < n; i++) {
    if (a[i] > s.top()) {
      while (!s.empty() && a[i] > s.top()) {
        s.pop();
      }
      s.push(a[i]);
    }
  }
  vector<int> res;
  while (!s.empty()) {
    res.push_back(s.top());
    s.pop();
  }
  for (int i = res.size() - 1; i >= 0; i--) {
    cout << res[i] << " ";
  }
  return 0;
}
