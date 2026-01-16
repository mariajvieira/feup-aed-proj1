#ifndef SCHEDULE_DATA_PARSING_H
#define SCHEDULE_DATA_PARSING_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <set>
#include "Lecture.h"
#include "Student.h"
#include "UC.h"
#include "Class.h"
using namespace std;

vector<Lecture> parsing_classes();
vector<Student> parsing_students_classes();
vector<UC> parsing_classes_per_uc();
vector<Class> lectures_per_class(vector<Lecture>& v_lectures);

#endif //SCHEDULE_DATA_PARSING_H
