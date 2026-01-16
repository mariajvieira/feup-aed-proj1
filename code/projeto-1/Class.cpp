#include "Class.h"

Class::Class(string a,vector<Lecture> b )
{
    ClassCode = a;
    Schedule = b;
}

string Class::get_ClassCode()
{
return ClassCode;
}
vector<Lecture> Class::get_Schedule()
{
return Schedule;
}
void Class::set_ClassCode(string s)
{
ClassCode = s;
}
void Class::set_Schedule(vector<Lecture> v)
{
Schedule = v;
}