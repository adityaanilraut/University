// main.cpp
// Raut, Aditya Anil
// araut1

#include <iostream>
using namespace std;
#include "vlist.h"
#include "video.h"
// Purpose:take input for user using getline also find what command 
// Input Parameters: takes input strings
// Output Parameters:Runs function print_function to print output
// Return Value: Always returns 0 if pass


void read_input(Vlist &vlist){
    string command;
    while (getline(cin, command)) {
        if (command == "insert") {
            string title, url, comment;
            float length;
            int rating;
            getline(cin, title);
            getline(cin, url);
            getline(cin, comment);
            cin >> length >> rating;
            cin.ignore(); // clear newline

            Video* new_video = new Video(title, url, comment, length, rating);
            vlist.insert(new_video);
        }
        else if (command == "print") {
            vlist.print();

        }
        else if (command == "length") {
            cout<<vlist.length()<<endl;
        }
        else if (command == "lookup") {
            string lookup;
            getline(cin, lookup);
            vlist.lookup(lookup);
        }
        else if (command == "remove") {
            string remove;
            getline(cin, remove);
            vlist.remove(remove);
        }
        else {
            cerr << "<" << command << "> is not a legal command, giving up." << endl;
            return;
        }
    }



}
// Purpose:Program start here
// Input Parameters: takes input strings
// Output Parameters:Runs function print_function to print output
// Return Value: Always returns 0 if pass


int main() {
    Vlist vlist;
    read_input(vlist);
    return 0;
}