#ifndef SCHEDULE_REQUESTS_FUNCTIONS_H
#define SCHEDULE_REQUESTS_FUNCTIONS_H
#include "data_parsing.h"
#include "consult_functions.h"

int num_students_per_UC_class(string uc_code, string class_code,vector<Student>& v);
int max_num(vector<UC>& v,vector<Student>& v_student);
int min_num(vector<UC>& v,vector<Student>& v_student);
void add_to_UC(vector<Student>& v,vector<UC>& v_uc,vector<Class>& v_class,stack<vectors>& current_data,stack<string>& history);
void remove_from_UC(vector<Student>& v,vector<UC>& v_uc,vector<Class>& v_class,stack<vectors>& current_data,stack<string>& history);
void switch_UC(vector<Student>& v,vector<UC>& v_uc,vector<Class>& v_class,stack<vectors>& current_data,stack<string>& history);
void switch_class(vector<Student>& v,vector<UC>& v_uc,vector<Class>& v_class,stack<vectors>& current_data,stack<string>& history);
int balance(vector<UC>& v,vector<Student>& v_student);
void go_back(stack<vectors>& data_history,stack<string>& history,vector<Student>& v,vector<UC>& v_uc,vector<Class>& v_class);

#endif //SCHEDULE_REQUESTS_FUNCTIONS_H
