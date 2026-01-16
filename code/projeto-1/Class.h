#ifndef SCHEDULE_CLASS_H
#define SCHEDULE_CLASS_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include "Lecture.h"
using namespace std;

class Class {

private:

    string ClassCode;
    vector<Lecture> Schedule;

public:
    Class(): ClassCode("ClassCode"), Schedule(){}
    Class(string a,vector<Lecture> b );
    string get_ClassCode();
    vector<Lecture> get_Schedule();
    void set_ClassCode(string s);
    void set_Schedule(vector<Lecture> v);


};


#endif //SCHEDULE_CLASS_H
