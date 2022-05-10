#include "Node.h"
#include "Problem.h"
#include <iostream>
#include <string>
#include <cmath>
#include <math.h>
#include <vector>

using namespace std;
//set length quality of node to be the weight of the priority of a node

Problem::Problem(){}

void Problem::solve(){
  int userInput = 2;
  while(userInput > 2 || userInput < 1){
    cout << "Welcome to 862162367 8 puzzle solver. Type 1 to use a default puzzle, or 2 to use your own puzzle." << endl;
    cin >> userInput;
  }
  string s1;
  string s2;
  string s3;
  if(userInput == 2){
    cout << "Enter your puzzle, use a b to represent a blank" << endl;
    cout << "Enter the first row, use space between numbers" << endl;
    cin >> s1;
    cout << "Enter the second row, use space between numbers" << endl;
    cin >> s2;
    cout << "Enter the third row, use space between numbers" << endl;
    cin >> s3;
  }
  string temp = "";
  temp += s1;
  temp += s2;
  temp += s3;

  initialState = temp;

  int userInput2 = 4;
  while(userInput2 < 1 || userInput2 > 3){
    cout << "Type the number of the algorithm you want to run" << endl;
    cout << "1. Uniform Cost Search" << endl;
    cout << "2. A* with the Misplaced Tile Heurstic" << endl;
    cout << "3. A* with the Euclidean Distance Heurstic" << endl;
    cin >> userInput2;
  }

  //use hashmaps
    //Run Uniform Cost
    bool goalFound = false;
    Node* root = new Node(initialState);
    //Initialize frontier with root node as 1st element
    vector<Node*> frontier;
    vector<int> priority;
    vector<string> visitedNodes;
    frontier.push_back(root);
    priority.push_back(0);
    bool isIn1 = false;
    bool isIn2 = false;
    bool isIn3 = false;
    bool isIn4 = false;
  
    while(!goalFound){
      if(frontier.size() == 0){
        break;
      }
      //Grab the top item from frontier
      int pri = priority.at(0);
      //index of the highest priority item (closest distance to root)
      int index = 0;
      for(int i = 0; i < priority.size(); i++){
        if(priority.at(i) <= pri){
          index = i;
          pri = priority.at(i);
        }
        //need to delete item from the frontier
      }
      Node* currentNode = frontier.at(index);
      frontier.erase (frontier.begin() + index);
      cout << endl;
      cout << "Expanding state" << endl;
      cout << endl;
      printPattern(currentNode->getPattern());
      if(comparePattern(currentNode->getPattern(), goalState) == true){
        cout << "Depth: " << depth(currentNode);
        cout << "GOAL!!!" << endl;
        return;
      }
      visitedNodes.push_back(currentNode->getPattern());
      /* run the operations on the current node */
      //bools to see if there exists a pattern identical to after running the opporations
      bool node1 = false;
      bool node2 = false;
      bool node3 = false;
      bool node4 = false;
      string op1 = shiftUp(currentNode->getPattern());
      string op2 = shiftDown(currentNode->getPattern());
      string op3 = shiftLeft(currentNode->getPattern());
      string op4 = shiftRight(currentNode->getPattern());
      int prio1 = 0;
      int prio2 = 0;
      int prio3 = 0;
      int prio4 = 0;
      //check to see if the state is in the visitedNodes
      for(int i = 0; i < visitedNodes.size(); i++){
          if(!comparePattern(visitedNodes.at(i), op1)){
                  node1 = true;
            }
          if(!comparePattern(visitedNodes.at(i), op2)){
                  node2 = true;
            }
          if(!comparePattern(visitedNodes.at(i), op3)){
                  node3 = true;
            }
          if(!comparePattern(visitedNodes.at(i), op4)){
                  node4 = true;
            }
      if(userInput2 == 1){
        //check the frontier
        for(int i = 0; i < frontier.size(); i++){
          if(!comparePattern(frontier.at(i)->getPattern(), op1) && node1 == false ){
                isIn1 = true;
            }
            if(!comparePattern(frontier.at(i)->getPattern(), op2) && node2 == false){
              isIn2 = true;
            }
            if(!comparePattern(frontier.at(i)->getPattern(), op3) && node3 == false){
              isIn3 = true;
              }
            if(!comparePattern(frontier.at(i)->getPattern(), op4) && node4 == false){
              isIn4 = true;
              }
          }
        } else if(userInput2 == 2){
          prio1 = amtMisplaced(op1);
        prio2 = amtMisplaced(op2);
        prio3 = amtMisplaced(op3);
        prio4 = amtMisplaced(op4);
          for(int i = 0; i < frontier.size(); i++){
          if(!comparePattern(frontier.at(i)->getPattern(), op1) && node1 == false){
                isIn1 = true;
            }
            if(!comparePattern(frontier.at(i)->getPattern(), op2) && node2 == false){
                  isIn2 = true;   
                  int prio = amtMisplaced(op2);
              }
            if(!comparePattern(frontier.at(i)->getPattern(), op3) && node3 == false){
                isIn3 = true; 
                int prio = amtMisplaced(op3);
              }
            if(!comparePattern(frontier.at(i)->getPattern(), op4) && node4 == false){
                isIn3 = true;  
                int prio = amtMisplaced(op4);
              }
          }
        } else {
          for(int i = 0; i < frontier.size(); i++){
          if(!comparePattern(frontier.at(i)->getPattern(), op1) && node1 == false){
                  isIn1 = true;
                  int prio = computeDist(op1);
            }
            if(!comparePattern(frontier.at(i)->getPattern(), op2) && node2 == false){
                  isIn2 = true;
                  int prio = computeDist(op2);
              }
            if(!comparePattern(frontier.at(i)->getPattern(), op3) && node3 == false){
                  isIn3 = true; 
                  int prio = computeDist(op3);
              }
            if(!comparePattern(frontier.at(i)->getPattern(), op4) && node4 == false){
                  isIn4 = true;
                  int prio = computeDist(op4);
              }
          }
        }
      //Check if they are in the visitedNodes or is in the frontier
        if(isIn1 == false){
          Node* n1 = new Node(op1);
          n1->prev = currentNode;
          frontier.push_back(n1);
          priority.push_back(pri + 1 + prio1);
        }
        if(isIn2 == false){
          Node* n1 = new Node(op2);
          n1->prev = currentNode;
          frontier.push_back(n1);
          priority.push_back(pri + 1 + prio2);
        }
        if(isIn3 == false){
          Node* n1 = new Node(op3);
          n1->prev = currentNode;
          frontier.push_back(n1);
          priority.push_back(pri + 1 + prio3);
        }
        if(isIn4 == false){
          Node* n1 = new Node(op4);
          n1->prev = currentNode;
          frontier.push_back(n1);
          priority.push_back(pri + 1 + prio4);
        }      
      }
    }
  
}

string Problem::shiftUp(string input){
  string shifted = input;
  if(shifted.at(0) == 'b' || shifted.at(1) == 'b' || shifted.at(2) == 'b'){
    return shifted;
  }
  for(int i = 0; i < shifted.size(); i++){
      if(shifted.at(i) == 'b'){
        char temp = shifted.at(i-3);
        shifted.at(i-3) = 'b';
        shifted.at(i) = temp;
        return shifted;
    }
  }
  cout << "We should not get here" << endl;
  return shifted;
}

string Problem::shiftDown(string input){
  string shifted = input;
  if(shifted.at(6) == 'b' || shifted.at(7) == 'b' || shifted.at(8) == 'b'){
    return shifted;
  }
  for(int i = 0; i < shifted.size(); i++){
      if(shifted.at(i) == 'b'){
        char temp = shifted.at(i+3);
        shifted.at(i+3) = 'b';
        shifted.at(i) = temp;
        return shifted;
    }
  }
  cout << "We should not get here" << endl;
  return shifted;
}

string Problem::shiftLeft(string input){
  string shifted = input;
  if(shifted.at(0) == 'b' || shifted.at(3) == 'b' || shifted.at(6) == 'b'){
    return shifted;
  }
  for(int i = 0; i < shifted.size(); i++){
      if(shifted.at(i) == 'b'){
        char temp = shifted.at(i-1);
        shifted.at(i-1) = 'b';
        shifted.at(i) = temp;
        return shifted;
    }
  }
  cout << "We should not get here" << endl;
  return shifted;
}

string Problem::shiftRight(string input){
  string shifted = input;
  if(shifted.at(2) == 'b' || shifted.at(5) == 'b' || shifted.at(8) == 'b'){
    return shifted;
  }
  for(int i = 0; i < shifted.size(); i++){
      if(shifted.at(i) == 'b'){
        char temp = shifted.at(i+1);
        shifted.at(i+1) = 'b';
        shifted.at(i) = temp;
        return shifted;
    }
  }
  cout << "We should not get here" << endl;
  return shifted;
}

void Problem::printPattern(string pattern){
  cout << pattern.at(0) << pattern.at(1) << pattern.at(2) << endl;
  cout << pattern.at(3) << pattern.at(4) << pattern.at(5) << endl;
  cout << pattern.at(6) << pattern.at(7) << pattern.at(8) << endl;
}

int Problem::depth(Node* node){
  int counter = 0;
  Node* temp = node;
  while(temp->prev != nullptr){
    temp = temp->prev;
    counter++;
  }
  return counter;
}

int Problem::amtMisplaced(string pattern){
  int counter = 0;
  for(int i = 0; i < pattern.size(); i++){
    if(pattern.at(i) != goalState.at(i)){
      counter++;
    }
  }
  return counter;
}

int Problem::computeDist(string pattern){
  int dist = 0;
  double accumulator = 0;
  for(int i = 0; i < initialState.size(); i++){
    //string index = initialState.at(i);
  }
  dist = (int) dist;
  return dist;
}
  
//returns true if they are identical
// false otherwise
bool Problem::comparePattern(string pattern, string pattern2){
  return pattern == pattern2;
}