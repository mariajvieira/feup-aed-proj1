#include "Lecture.h"

Lecture::Lecture(string a,string b,string c,float d,float e,string f)
{
    ClassCode=a;
    UcCode=b;
    Weekday=c;
    StartHour=d;
    Duration=e;
    Type=f;
}
string Lecture::get_ClassCode()
{
    return ClassCode;
}
string Lecture::get_UcCode()
{
    return UcCode;
}
string Lecture::get_Weekday()
{
    return Weekday;
}
float Lecture::get_StartHour()
{
    return StartHour;
}
float Lecture::get_Duration()
{
    return Duration;
}
string Lecture::get_Type()
{
    return Type;
}
void Lecture::set_ClassCode(string s){
    ClassCode = s;
}
void Lecture::set_UcCode(string s){
    UcCode = s;
}
void Lecture::set_Weekday(string s){
    Weekday = s;
}
void Lecture::set_StartHour(float f){
    StartHour = f;
}
void Lecture::set_Duration(float f){
    Duration = f;
}
void Lecture::set_Type(string s){
    Type = s;
}