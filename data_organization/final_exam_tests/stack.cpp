#include <iostream>
using namespace std;

#define MAX 1000

struct STACK {
  int data[MAX];
  int top;
};

// Set the top of the stack to -1
void init(STACK &S) { S.top = -1; }

// If the top of the stack is -1, the stack is empty
bool isEmpty(STACK &S) { return S.top == -1; }

void push(STACK &S, int K) {
  if (S.top == MAX - 1) {
    cout << "Stack is full" << endl;
    return;
  }
  S.data[++S.top] = K;
}

int pop(STACK &S) { return S.data[S.top--]; }

void toBinary(int d) {
  STACK S;
  init(S);

  while (d > 0) {
    push(S, d % 2);
    d /= 2;
  }

  while (!isEmpty(S)) {
    cout << pop(S);
  }
  cout << endl;
}

int main() {
  toBinary(10);
  return 0;
}