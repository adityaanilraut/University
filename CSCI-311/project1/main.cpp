#include "bst.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    Bst tree;
    string command;
    
    while (cin >> command) {
        if (command == "echo") {
            string message;
            cin.ignore();
            getline(cin, message);
            cout << message << endl;
        }
        else if (command == "insert") {
            string value;
            cin.ignore();
            getline(cin, value);
            if (!tree.insert(value)) {
                cerr << "insert <" << value << "> failed. String already in tree." << endl;
            }
        }
        else if (command == "count") {
            cout << tree.getCount() << endl;
        }
        else if (command == "find") {
            string value;
            cin.ignore();
            getline(cin, value);
            if (tree.find(value)) {
                cout << "<" << value << "> is in tree." << endl;
            } else {
                cout << "<" << value << "> is not in tree." << endl;
            }
        }
        else if (command == "print") {
            vector<string> values;
            tree.dft(values);
            cout << "{";
            for (size_t i = 0; i < values.size(); i++) {
                cout << values[i];
                if (i < values.size() - 1) {
                    cout << ", ";
                }
            }
            cout << "}" << endl;
        }
        else if (command == "breadth") {
            vector<string> values;
            tree.bft(values);
            cout << "{";
            for (size_t i = 0; i < values.size(); i++) {
                cout << values[i];
                if (i < values.size() - 1) {
                    cout << ", ";
                }
            }
            cout << "}" << endl;
        }
        else if (command == "height") {
            cout << tree.getHeight() << endl;
        }
        else if (command == "balanced") {
            if (tree.isBalanced()) {
                cout << "Tree is balanced." << endl;
            } else {
                cout << "Tree is not balanced." << endl;
            }
        }
        else if (command == "rebalance") {
            tree.rebalance();
        }
        else {
            cerr << "Illegal command <" << command << ">." << endl;
            string dummy;
            getline(cin, dummy);
        }
    }
    
    return 0;
}