#include "Student.h"

Student:: Student(): StudentCode("StudentCode"), StudentName("StudentName"), Schedule(Schedule){}
Student::Student(string a,string b, vector<Lecture> c)
{
    StudentCode = a;
    StudentName = b;
    Schedule = c;

}
string Student::get_StudentCode()
{
    return StudentCode;
}
void Student::add_Class(const Lecture& aClass)
{
    Schedule.push_back(aClass);
}
void Student::set_StudentName(string s)
{
    StudentName = s;
}
void Student::set_StudentCode(string s)
{
    StudentCode = s;
}
void Student::set_Schedule(vector<Lecture> s)
{
    sort(s.begin(),s.end(), [](Lecture a, Lecture b)
    {
        return (a.get_StartHour()<b.get_StartHour());
    });
    Schedule = s;
}


string Student::get_StudentName()
{
    return StudentName;
}
vector<Lecture> Student::get_Schedule()
{
    return Schedule;
}

