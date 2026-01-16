#ifndef SCHEDULE_CONSULT_FUNCTIONS_H
#define SCHEDULE_CONSULT_FUNCTIONS_H

#include <stack>
#include "data_parsing.h"
struct vectors {
    vector<Student> v_students_classes;
    vector<UC> v_classes_per_uc;
    vector<Class> v_lectures_per_class;
};

void print_student_schedule(vector<Student> v);
void print_class_schedule(vector<Class> v);
void print_students_given_class(vector<Student> v);
void print_students_given_course(vector<Student> v);
void print_students_given_year(vector<Student> v);
void print_students_registered_in_at_least_n_UCs(vector<Student> v);
void print_num_students_per_uc(vector<Student> v);
void num_students_per_class(vector<UC> v_uc, vector<Student> v_stu);
void num_students_class_per_uc(vector<UC> v_uc, vector<Student> v);
void uc_class_student(vector<UC> v_uc, vector<Student> v);
void consult_history(stack<string> history);

#endif //SCHEDULE_CONSULT_FUNCTIONS_H