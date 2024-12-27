#include <iostream>
#include <string>
#include <set>
using namespace std;
const int ALPHABET_SIZE = 26;

class Trie {
private:
    class Node {
    public:
        Node* children[ALPHABET_SIZE];
        bool isEndOfWord;
        set<int> lineNumber;
        char data;

        Node(char c) 
        {
            data = c;
            isEndOfWord = false;
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                children[i] = nullptr;
            }
        }
        
        Node() 
        {
            data = '\0';
            isEndOfWord = false;
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                children[i] = nullptr;
            }
        }
    };

    Node* root;

    // Helper function for printing words in the Trie
    void printWords(Node* node, string prefix) {
        if (node == nullptr)
            return;

        if (node->data != '\0') {
            prefix += node->data;
        }

        if (node->isEndOfWord) {
            cout << prefix << " ";
            //int size=sizeof(node->lineNumber)/sizeof(int);
            /*for(int i=0;i<size;i++){
                if(node->lineNumber[i+1]!=0){
                    cout<<node->lineNumber[i]<<", ";
                }
                else{
                    cout<<node->lineNumber[i];
                    break;
                }
            }*/
            string ss;
            for(int i :node->lineNumber){
                string a=to_string(i);
                a=a+", ";
                ss=ss+a;
            }
            ss.pop_back();
            ss.pop_back();
            cout<<ss<<endl;
        }

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            printWords(node->children[i], prefix);
        }
    }

public:
    Trie() : root(new Node()) {}

    void insert(const string& word,int lineNo) {
        Node* temp = root;
        for (char c : word) {
            if(int(c)<97){
                c=c+32;
            }
            int index = c - 'a';
            if (temp->children[index]==nullptr) {
                temp->children[index] = new Node(c);
            }
            temp = temp->children[index];
        }
        temp->isEndOfWord = true;
        temp->lineNumber.insert(temp->lineNumber.end(),lineNo);
    }

    void printWords() {
        printWords(root, "");
    }
};

int main() {
    Trie trie;
    string line;
    int count=0;
    while(getline(cin,line)){
        count=count+1;
        string word;
        for(char c : line){
            if(isalpha(c)){
                word = word+c;
                }
            else{
                //cout<<word<<endl;
                trie.insert(word,count);
                word.clear();
            }
        }

        
        

    }
    trie.printWords();
    return 0;
}