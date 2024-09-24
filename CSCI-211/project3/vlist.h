#ifndef VLIST_H
#define VLIST_H

#include "video.h"
// code was provided, most of the code was just formated
// Purpose:declare all functions to be used


// class Vlist is declare here
// contians the structure of the object vlist. all variables are written using m_

class Vlist {
    public:
    Vlist()
    {
    m_head = NULL;
    }
    void insert(Video *new_video);
    void print();
    void lookup(string title);
    void remove(string title);
    int length();
    private:
    bool __ifexist(Video* newVideo); // decleration of the internal private functiom
    class Node {
        public:
        Node(Video *video, Node *next){
            m_video = video;
            m_next = next;
            }
        Video *m_video;
        Node *m_next;
        };
    Node *m_head;
};
#endif
