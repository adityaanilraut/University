#include <iostream>
#include <string>
#include <string>
#include <set>
using namespace std;
class TST {
private:
    class Node {
    public:
        char data;
        bool isEndOfWord;
        set<int> lineNumber;
        Node* left;
        Node* equal;
        Node* right;
        
        Node(char val) {
            data = val;
            isEndOfWord = false;
            
            left = nullptr;
            equal = nullptr;
            right = nullptr;
        }
    };
    
    Node* root;
    
    // Helper recursive functions
    Node* insert(Node* node, const char* word,int lineNo) {
        
        //if(*word >= 'A' && *word <= 'Z'){
          //  *word = *word + ('a' - 'A');
          //  cout<<*word<<endl;

        //}
        
        if(node==nullptr)
        {
        node = new Node(*word);
        }
        
        if(*word < node->data)
            node->left = insert(node->left, word,lineNo);
        else if(*word > node->data)
            node->right = insert(node->right, word,lineNo);
        else {
            if (*(word + 1) != '\0')
                node->equal = insert(node->equal, word + 1,lineNo);
            else
                node->isEndOfWord = true;
                node->lineNumber.insert(node->lineNumber.end(),lineNo);
        }
        
        return node;
    }
    
   void printWords(Node* node, string prefix) {
    if (node==nullptr) return;

    printWords(node->left, prefix);

    prefix += node->data;
    if (node->isEndOfWord) {
        cout << prefix << " ";
        int size=sizeof(node->lineNumber)/sizeof(int);
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

    printWords(node->equal, prefix);
    printWords(node->right, prefix.substr(0, prefix.size() - 1));  // remove the last character for the right subtree
    
}

public:
    TST(): root(nullptr) {}
    
    void insert(string word,int lineNo) {
        if(word[0]<'a'){
            word[0]=word[0]+32;

        }
        root = insert(root, word.c_str(),lineNo);
    }
    
  void printWords() {
    string prefix = "";
    printWords(root, prefix);
}
};

int main() {
    TST tst;
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
                tst.insert(word,count);
                word.clear();
            }
        }

        
        

    }

    // Inserting some words into TST
    //tst.insert("batman");
    //tst.insert("bati");
    //tst.insert("batis");
   // tst.insert("batmaz");
    
    // Printing all words in TST alphabetically
    //cout << "Words stored in the TST (Alphabetically order): ";
    tst.printWords();
    cout << endl;
    return 0;
}
