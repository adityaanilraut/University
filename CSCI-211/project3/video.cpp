
// video.cpp
// Raut, Aditya Anil
// araut1


#include <iostream>


using namespace std;
#include "video.h"


// Purpose:constructor to store all input values
// Input Parameters:  title,  url,  comment,  length,  rating
// Output Parameters:store all input values

Video::Video(string title, string url, string comment, float length, int rating){
    this->title=title;
    this->url=url;
    this->comment=comment;
    this->length=length;
    this->rating=rating;
}

// Purpose: Print the bar chart based on the input array
// outputs all the values on an object - title,  url,  comment,  length,  rating
// Output Parameters: None
// Return Value: None
void Video::print() {
    cout << this->title <<", ";
    cout << this->url <<", ";
    cout <<  this->comment <<", ";
    cout << this->length <<", ";
    for(int i=0;i<this->rating;i++){
        cout << "*";
    }
    cout <<endl;
}
// old code did not changed 
// Purpose:Compare function to find the type of sorting to do on a given input
// Input Parameters: video obj and sort string
// Output Parameters:bool value
// Return Value: true or false
bool Video::compare(Video* otherVideo, string sort) {
    if(sort=="rating") {
        return compareRatings(otherVideo);
    }
    else if (sort=="length") {
        return compareLengths(otherVideo);
    }
    else if (sort=="title") {
        return compareTitles(otherVideo);
    }
}
// old code did not changed 
// Purpose:Compare function to compare two rating values
// Input Parameters: video obj
// Output Parameters:bool value
// Return Value: true or false
bool Video::compareRatings(Video *otherVideo) {
    return  this->rating < otherVideo->rating;
}
// old code did not changed 
// Purpose:Compare function to compare two length values
// Input Parameters: video obj
// Output Parameters:bool value
// Return Value: true or false
bool Video::compareLengths(Video *otherVideo) {
    return this->length > otherVideo->length  ;

}
// old code did not changed 
bool Video::compareTitles(Video *otherVideo) {
    return   this->title > otherVideo->title;

}
//getter command for getting the title of the video object
string Video::getTittle(){
    return this->title;

}
