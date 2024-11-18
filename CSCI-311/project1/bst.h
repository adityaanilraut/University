#ifndef BST_H
#define BST_H

#include <string>
#include <vector>
using namespace std;

class Bst {
public:
  Bst();
  ~Bst();

  bool insert(string value);

  bool find(string value);
  void dft(vector<string> &values);

  void bft(vector<string> &values);

   bool isBalanced();

  int getHeight();
  void insertFromVector(vector<string>& values, int start, int end);

  void rebalance();


  int getCount();

public:
  class Node {
  public:
    Node(string value);
    ~Node();
    string m_value;
    Node *m_left;
    Node *m_right;
  };
  Node *m_root;
  int m_count;
};
#endif
