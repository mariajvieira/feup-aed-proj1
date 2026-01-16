#ifndef SCHEDULE_LECTURE_H
#define SCHEDULE_LECTURE_H
#include <list>
#include <string>
using namespace std;

class Lecture {

private:
    string ClassCode;
    string UcCode;
    string Weekday;
    float StartHour;
    float Duration;
    string Type;

public:
    Lecture(): ClassCode("ClassCode"), UcCode("UcCode"), Weekday("Weekday"), StartHour(0.0), Duration(0.0), Type("Type"){}
    Lecture(string a, string b, string c, float d, float e, string f);
    string get_ClassCode();
    string get_UcCode();
    string get_Weekday();
    float get_StartHour();
    float get_Duration();
    string get_Type();
    void set_ClassCode(string s);
    void set_UcCode(string s);
    void set_Weekday(string s);
    void set_StartHour(float f);
    void set_Duration(float f);
    void set_Type(string s);

};

#endif //SCHEDULE_LECTURE_H