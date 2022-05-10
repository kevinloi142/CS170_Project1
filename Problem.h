#ifndef PROBELM_H_
#define PROBLEM_H_
#include <string>
#include "Node.h"

using namespace std;
class Problem{
  public:
    Problem();
    string initialState;
    string goalState = "12345678b";
    void solve();
  private: 
    string shiftUp(string);
    string shiftDown(string);
    string shiftLeft(string);
    string shiftRight(string);
    void printPattern(string);
    int depth(Node*);
    int amtMisplaced(string);
    int computeDist(string);
    bool comparePattern(string, string);
};
#endif