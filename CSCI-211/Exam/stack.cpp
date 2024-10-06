#include<iostream>
using namespace std;
class Linkedlist
{
private:
    class Node
    {
    public:
        int data;
        Node * next;
    
        Node(int d, Node * n){
            this->data=d;
            this->next=n;
        };
        
    };
    Node* head;
    
    
    
public:
    

    Linkedlist(/* args */){
        head=nullptr;
    }
    

    void push(int value){
        head= new Node(value, head);

    }
    void pop(){
       Node* temp=head;
       head=head->next;
       delete temp;

    }

    void popAll(){
        while(head!=nullptr){
       Node* temp=head;
       head=head->next;
       delete temp;
       }

    }
    void insertAtTail(int value){
        if(head==nullptr){
        head= new Node(value, head);
        }
        else{
            Node* newNode= new Node(value, nullptr);
            Node* current=head;
            Node* pervious=nullptr;
            while(current!=nullptr){
                pervious=current;
                current=current->next;
                }
            pervious->next=newNode;
            }

    }
    void print(){
        Node *current=head;
        while(current!=nullptr){
            cout<<current->data<<endl;
            current=current->next;
        }

    }
    Linkedlist merge(Linkedlist* l1,Linkedlist *l2){
        Linkedlist result;
        Node * temp1=l1->head;
        Node * temp2=l1->head;
        while (temp1!=nullptr&&temp2!=nullptr){
            if(temp1->data<=temp2->data){
                result.push(temp1->data);
                temp1=temp1->next;
                }
            else{
                result.push(temp2->data);
                temp2=temp2->next;
                }
            }
        while (temp1!=nullptr){
            result.push(temp1->data);
            temp1=temp1->next;

        }
        while (temp2!=nullptr){
            result.push(temp2->data);
            temp2=temp2->next;
        }

        return result;

        
        


    }
    

    ~Linkedlist();
};
int main(){
    Linkedlist *l1=new Linkedlist();
    Linkedlist *l2=new Linkedlist();
    l1->push(1);
    l1->push(2);
    l1->push(3);
    l2->push(4);
    l2->push(5);
    l2->push(6);
    //l1->insertAtTail(4);
   // l1->pop();
   // l1->print();
   // l1->popAll();
    l1->print();
    l2->print();
    Linkedlist  *a=merge(l1,l2);
    a->print();

    return 0;
}
