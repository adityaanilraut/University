#include <iostream>
#include <string>
#include <queue>
using namespace std;

class BinaryTree {
private:
    class Node {
    public:
        int data;
        Node* left;
        Node* right;

        Node(int data, Node* left = nullptr, Node* right = nullptr) {
            this->data = data;
            this->left = left;
            this->right = right;
        }
        void addDataInNode(int d)
        {
            queue<Node*> q;
            q.push(this);
            while(!q.empty()){
                Node * a=q.front();
                q.pop();
                if(a->left==nullptr){
                   a->left =new Node(d,nullptr,nullptr);
                   break;

                }
                if(a->right==nullptr){
                    a->right =new Node(d,nullptr,nullptr);
                    break;

                }
                q.push(a->left);
                q.push(a->right);



            }
        }
        
    };

    Node* root;

public:
    BinaryTree() {
        root = nullptr;
    }
    
    void addData(int d){
        if(root==nullptr){
            root=new Node(d,nullptr,nullptr);
        }
        else{
            root->addDataInNode(d);
        }
    }
   void preOrder(){

    if(root==nullptr){
        return;
    }
    else{
        return __preOrder(root,0);
    }
   }
   void __preOrder(Node * root,int a){
    if(root==nullptr){
        return;
    }
    else{
        int index=a;
        string s="";
        for(int i=0;i<index;i++){
            s=s+" ";
            }
        cout<<s<<root->data<<endl;
        __preOrder(root->left,index+1);
        __preOrder(root->right,index+1);
        }

   }
   void postOrder(){

    if(root==nullptr){
        return;
    }
    else{
        return __postOrder(root,0);
    }
   }
   void __postOrder(Node * root,int a){
    if(root==nullptr){
        return;
    }
    else{
        int index=a;
        string s="";
        for(int i=0;i<index;i++){
            s=s+" ";
            }
        
        __postOrder(root->left,index+1);
        __postOrder(root->right,index+1);
        cout<<s<<root->data<<endl;
        }

   }
   void inOrder(){

    if(root==nullptr){
        return;
    }
    else{
        return __inOrder(root,0);
    }
   }
   void __inOrder(Node * root,int a){
    if(root==nullptr){
        return;
    }
    else{
        int index=a;
        string s="";
        for(int i=0;i<index;i++){
            s=s+" ";
            }
        
        __inOrder(root->left,index+1);
        cout<<s<<root->data<<endl;
        __inOrder(root->right,index+1);
        
        }

   }
   void levelOrder(){

    if(root==nullptr){
        return;
    }
    else{
        return __levelOrder(root,0);
    }
   }
   void __levelOrder(Node * root,int a){
    if(root==nullptr){
        return;
    }
    else{
        queue<Node*> q;
        q.push(root);
        while(!q.empty()){
            Node* a=q.front();
            cout<<a->data<<endl;
            q.pop();
            if(a->left!=nullptr){
                q.push(a->left);
                }
            if(a->right!=nullptr){
                q.push(a->right);
                }
          
        }}

   }
   int adding(){

    if(root==nullptr){
        return 0;
    }
    else{
        return __adding(root);
    }
   }
   int __adding(Node * root){
    if(root==nullptr){
        return 0;
    }
    else{
        return __adding(root->left)+__adding(root->right)+root->data;



        }
    }
    int count(){

    if(root==nullptr){
        return 0;
    }
    else{
        return __count(root);
    }
   }
   int __count(Node * root){
    if(root==nullptr){
        return 0;
    }
    else{
        return __count(root->left)+__count(root->right)+1;



        }
    }
    int countleaf(){

    if(root==nullptr){
        return 0;
    }
    else{
        return __countleaf(root)/2;
    }
   }
   int __countleaf(Node * root){
    if(root==nullptr){
        return 1;
    }
    else{
        return __countleaf(root->left)+__countleaf(root->right);



        }
    }
    void addBST(int data){
        if(root==nullptr){

           root=new Node(data,nullptr,nullptr);
        }
        else{
            __addBST(root,  data);

        }

    }
    Node* __addBST(Node* root,  int data){
        if(root==nullptr){

            return new Node(data,nullptr,nullptr);
        }
        else if(root->data>data){
            root->left= __addBST(root->left, data);
            return root;
        }
        else if(root->data<data){
            root->right= __addBST(root->right, data);
            return root;

        }
        else{
            root->left= __addBST(root->left, data);
            return root;

        }




    }
    

    

   

   

};

int main() {
    BinaryTree *b1=new BinaryTree();
    BinaryTree *b2=new BinaryTree();
    //b1->addData();
    //b1->addData(2);
    //b1->addData(3);
    //b1->addData(4);
    //b1->addData(5);
    //b1->addData(6);
    //b1->addData(7);

    b2->addBST(10);
    b2->addBST(5);
    b2->addBST(20);
    b2->addBST(2);
    b2->addBST(7);
    b2->addBST(15);
    b2->addBST(25);
    

    // Call the public method to start preorder traversal from the root
    b2->preOrder();
    cout<<b2->adding()<<endl;
    cout<<b2->count()<<endl;
    cout<<b2->countleaf()<<endl;

    // Clean up to avoid memory leaks
    delete b2;

    return 0;
}
