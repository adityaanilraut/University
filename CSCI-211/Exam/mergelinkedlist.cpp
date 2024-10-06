#include <iostream>
using namespace std;

// Definition for a node in the linked list
class Node {
public:
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// LinkedList class to handle the creation and operations on the linked list
class LinkedList {
public:
    Node* head;

    LinkedList() : head(nullptr) {}

    // Function to insert a new node at the end of the list
    void insert(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Function to print the linked list
    void printList() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// Function to merge two sorted linked lists using recursion
Node* mergeSortedLists(Node* l1, Node* l2) {
    // Base cases
    if (!l1) return l2;
    if (!l2) return l1;

    // Recursively merge the lists
    if (l1->data < l2->data) {
        l1->next = mergeSortedLists(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeSortedLists(l1, l2->next);
        return l2;
    }
}

int main() {
    // Create two linked lists
    LinkedList list1;
    LinkedList list2;

    // Insert elements into list1 (sorted)
    list1.insert(1);
    list1.insert(3);
    list1.insert(5);

    // Insert elements into list2 (sorted)
    list2.insert(2);
    list2.insert(4);
    list2.insert(6);

    cout << "List 1: ";
    list1.printList();
    
    cout << "List 2: ";
    list2.printList();

    // Merge the two sorted lists
    Node* mergedHead = mergeSortedLists(list1.head, list2.head);

    // Print the merged list
    cout << "Merged List: ";
    LinkedList mergedList;
    mergedList.head = mergedHead;
    mergedList.printList();

    return 0;
}
