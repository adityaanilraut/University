
// video.h
// Raut, Aditya Anil
// araut1
#include <iostream>

using namespace std;

#ifndef VIDEO_H
#define VIDEO_H



class Video {
private:
    string title;
    string url;
    string comment;
    float length;
    int rating;
public:
    Video(string title, string url, string comment, float length, int rating);
    void print();
    // old code did not changed 
    bool compareRatings(Video *otherVideo);
    // old code did not changed 
    bool compareLengths(Video *otherVideo);
    // old code did not changed 
    bool compareTitles(Video *otherVideo);
    // old code did not changed 
    bool compare(Video* otherVideo, string sort);
    string getTittle();




};

#endif //VIDEO_H