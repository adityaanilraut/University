//
// Created by Aditya Raut on 9/11/24.
//

#ifndef COURSE_H
#define COURSE_H
using namespace std;

class course {
private:
    string dept;
    int number;
    int time;
public:
    course(string, int, int);
    void print();
    ~course() {

    }
};

#endif //COURSE_H
