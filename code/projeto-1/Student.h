#ifndef SCHEDULE_STUDENT_H
#define SCHEDULE_STUDENT_H
#include <string>
#include <vector>
#include "Lecture.h"
#include <algorithm>
using namespace std;

class Student {

private:
    string StudentCode;
    string StudentName;
    vector<Lecture> Schedule;

public:
    Student();
    Student(string a,string b, vector<Lecture> c);
    string get_StudentCode();
    void add_Class(const Lecture& aClass);
    void set_StudentName(string s);
    void set_StudentCode(string s);
    void set_Schedule(vector<Lecture> s);
    string get_StudentName();
    vector<Lecture> get_Schedule();
};

#endif //SCHEDULE_STUDENT_H