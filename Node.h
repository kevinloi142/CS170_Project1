#ifndef NODE_H_
#define NODE_H_
#include <string>

using namespace std;
class Node{
  string pattern;
  public:
    Node *prev;
    Node *next;
    Node(string pattern) : pattern(pattern), prev(0) , next(0){}
    string getPattern(){
      return pattern;
    }
};
#endif