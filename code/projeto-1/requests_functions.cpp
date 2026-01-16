#include "requests_functions.h"

int UCs_per_student(Student s)
{
    set<string> set_UCs;
    for (Lecture l: s.get_Schedule()) {
        set_UCs.insert(l.get_UcCode());
    }
    return set_UCs.size();
}

int num_students_per_UC_class(string uc_code, string class_code,vector<Student>& v)
{
    set<string> set_student;
    for(Student s : v)
    {
        for(Lecture l: s.get_Schedule())
        {
            if(l.get_UcCode()==uc_code && l.get_ClassCode()== class_code)
            {
                set_student.insert(s.get_StudentCode());
            }
        }
    }
    return set_student.size();
}

int max_num(vector<UC>& v,vector<Student>& v_student) {
    int max = 0;
    set<int> num_students;
    vector<int> n_students;
    for (UC uc : v) {
        for (string c : uc.get_ClassCodes()) {
            if (max < num_students_per_UC_class(uc.get_UcCode(), c,v_student))
                max = num_students_per_UC_class(uc.get_UcCode(), c,v_student);
        }
    }
    return (max);
}
int min_num(vector<UC>& v,vector<Student>& v_student) {
    int min = 26;
    set<int> num_students;
    vector<int> n_students;
    for (UC uc : v) {
        for (string c : uc.get_ClassCodes()) {
            if (min > num_students_per_UC_class(uc.get_UcCode(), c,v_student))
                min = num_students_per_UC_class(uc.get_UcCode(), c,v_student);
        }
    }
    return (min);
}
int balance(vector<UC>& v,vector<Student>& v_student) {
    return ( max_num(v,v_student) - min_num(v,v_student));
}

bool overlap(Lecture a,Lecture b)
{
    if((a.get_Type() == "T" && b.get_Type()=="T")
       || (a.get_Type() == "TP" && b.get_Type()=="T")
       || (a.get_Type() == "T" && b.get_Type()=="TP")
       || (a.get_Type() == "PL" && b.get_Type()=="T")
       || (a.get_Type() == "T" && b.get_Type()=="PL")) return false;

    float a_EndHour = a.get_StartHour() + a.get_Duration();
    float b_EndHour = b.get_StartHour() + b.get_Duration();

    if (a.get_Weekday() == b.get_Weekday()) {
        if ((a_EndHour > b.get_StartHour()) && (b.get_StartHour() > a.get_StartHour())
            || (b_EndHour > a.get_StartHour()) && (a.get_StartHour() > b.get_StartHour())
            || ((b.get_StartHour() > a.get_StartHour()) && (a_EndHour > b_EndHour))
            || ((a.get_StartHour() > b.get_StartHour()) && (b_EndHour > a_EndHour)))
            return true;
        else return false;
    }
    return false;
}

/**
 * Function to add a given Student to UC without inputs from user.
 *
 * No inputs from the user enables the use of the function to switch a UC of the user.
 * The addition of the UC depends on various conditions:
 * the class of the UC must have vacancy (no more than 26 students);
 * the lectures of the new UC cannot overlap any TP or PL lecture in the schedule of the student;
 * this change must maintain or improve balance of class occupation;
 * Function complexity:  O(n + m):  where 'n' is the number of Student objects and 'm' is the number of UC objects.
 *
 * @param v current vector of Students
 * @param v_uc current vector of UCs
 * @param v_class current vector of Classes
 * @param student_code given Student
 * @param uc_code UC to add to
 */
void add_s(vector<Student>& v,vector<UC>& v_uc,vector<Class>& v_class,string student_code, string uc_code) {

    set<string> classes;
    Student s;
    UC uc;

    for (Student student: v) {
        if (student.get_StudentCode() == student_code)
            s = student;
    }

    for (UC uc_: v_uc) {
        if (uc_.get_UcCode() == uc_code)
            uc = uc_;
    }

    for (string c: uc.get_ClassCodes()) {
        for (Class cl: v_class) {
            if (cl.get_ClassCode() == c) {
                for (Lecture l: cl.get_Schedule()) {
                    if ((l.get_UcCode() == uc_code) && (num_students_per_UC_class(uc_code, c, v) < 26)) {
                        if(s.get_Schedule().size()==0) classes.insert(c);
                        else
                        {
                            for (Lecture lec: s.get_Schedule()) {
                                if (!overlap(l, lec)) {
                                    classes.insert(c);
                                }
                            }
                        }

                    }
                }
            }
        }
    }

    if (classes.size() == 0) {
        cout << "The schedule of that UC is not compatible with the current student schedule.";
        return;
    }

    string chosen_class;

    if (balance(v_uc, v) > 4) {
        string min_class;
        set<string> s_classes;
        int min = 26;
        for (string s: classes) {
            if (min > num_students_per_UC_class(uc_code, s, v)) {
                min = num_students_per_UC_class(uc_code, s, v);
            }
        }
        for (string s: classes) {
            if (min == num_students_per_UC_class(uc_code, s, v))
                s_classes.insert(s);
        }
        cout << "\nIn order to promote balance of class occupation,\n"
             << "Student must be registered in one of the following classes: \n";
        for (string s: s_classes) cout << endl << s << " (" << num_students_per_UC_class(uc_code, s, v)
        << "/26 students)";
        bool a=false;
        while(!a)
        {
            cout << "\nChoose a Class (write the code of the class):" << endl;
            cin >> chosen_class;
            for (string s:s_classes)
            {
                if (s==chosen_class) {a=true;}
            }
            if (a) break;
            else
            {
                cout << "\nInvalid code of class.\n";
                continue;
            }
        }


    } else {
        set<string> classes_to_choose;
        for (string c: classes) {
            if ((num_students_per_UC_class(uc_code, c, v) == max_num(v_uc, v))
                && (num_students_per_UC_class(uc_code, c, v) + 1 - min_num(v_uc, v) > 4))
                continue;
            else classes_to_choose.insert(c);
        }
        cout << "\nClasses with vacancy:\n";
        for (string c: classes_to_choose) cout << endl << c;
        bool a=false;
        while(!a)
        {
            cout << "\nChoose a Class (write the code of the class):" << endl;
            cin >> chosen_class;
            for (string s:classes_to_choose)
            {
                if (s==chosen_class) {a=true;}
            }
            if (a) break;
            else
            {
                cout << "\nInvalid code of class.\n";
                continue;
            }
        }
    }

    vector<Lecture> finalsch;
    for (Student& s: v) {
        if (s.get_StudentCode() == student_code) {
            finalsch = s.get_Schedule();
            for (Class cl: v_class) {
                if (cl.get_ClassCode() == chosen_class) {
                    for (Lecture l: cl.get_Schedule()) {
                        if (l.get_UcCode() == uc_code) {
                            finalsch.push_back(l);
                        }
                    }
                }
            }
            s.set_Schedule(finalsch);
        }
    }
}

/**
 * Function to remove a given student from UC without inputs from user.
 *
 * No inputs from the user enables the use of the function to switch a UC of the user.
 * Function complexity : O(n) where 'n' is the number of Student objects in the v vector.
 * @param v current vector of Students
 * @param v_uc current vector of UCs
 * @param v_class current vector of Classes
 * @param student_code given Student
 * @param uc_code UC to remove from
 */
void remove_s(vector<Student>& v,vector<UC>& v_uc,vector<Class>& v_class,string student_code, string uc_code)
{
    vector<Lecture> finalsch;
    for (Student& s: v) {
        if (s.get_StudentCode()==student_code)
        {
            for (Lecture l:s.get_Schedule())
            {
                if (l.get_UcCode()!=uc_code) finalsch.push_back(l);
            }
            s.set_Schedule(finalsch);
            break;
        }
    }

}

/**
 * Function to add a given student to a UC with inputs from user.
 *
 * Call to add_s().
 * Function complexity:  O(n) where 'n' is the number of Student objects in the v vector.
 *
 * @param v current vector of Students
 * @param v_uc current vector of UCs
 * @param v_class current vector of Classes
 */
void add_to_UC(vector<Student>& v,vector<UC>& v_uc,vector<Class>& v_class,stack<vectors>& current_data,stack<string>& history)
{
    string student_code;
    string uc_code;
    bool valid = false;
    while (!valid) {
        cout << "\nCode of Student: ";
        cin >> student_code;
        cout << "Code of UC: ";
        cin >> uc_code;

        bool valid_s = false;
        for (Student s: v)
            if (s.get_StudentCode() == student_code) {
                valid_s = true;
                break;
            }
        bool valid_uc = false;
        for (UC uc: v_uc)
            if (uc.get_UcCode() == uc_code) {
                valid_uc = true;
                break;
            }
        if(valid_s && valid_uc) valid = true;
        if (!valid) cout << "\nInvalid code of Student or code of UC.\n";

        int num_UCs = 0;
        for (Student s: v) if (s.get_StudentCode() == student_code) num_UCs = UCs_per_student(s);
        if (num_UCs >= 7) {
            cout << "\nCan´t join any class - student is already registered in 7 UCs.\n";
            valid = false;
            continue;
        }

        for (Student s: v) {
            if (s.get_StudentCode() == student_code) {
                for (Lecture l: s.get_Schedule()) {
                    if (l.get_UcCode() == uc_code) {
                        cout << "\nStudent is already registered in UC " << uc_code << '.' << endl;
                        valid = false;
                        break;
                    }
                }
            }
        }

    }
    add_s(v,v_uc,v_class,student_code,uc_code);
    history.push("Student "+ student_code + " was added in UC " + uc_code);
    vectors a;
    a.v_students_classes= v;
    a.v_classes_per_uc=v_uc;
    a.v_lectures_per_class=v_class;
    current_data.push(a);
}

/**
 * Function to remove a given student from UC with inputs from user.
 *
 * Call to remove_s().
 * Function complexity: O(n) where 'n' is the number of Student objects in the v vector.
 *
 * @param v current vector of Students
 * @param v_uc current vector of UCs
 * @param v_class current vector of Classes
 */
void remove_from_UC(vector<Student>& v,vector<UC>& v_uc,vector<Class>& v_class,stack<vectors>& current_data,stack<string>& history)
{
    string student_code;
    string uc_code;
    bool valid = false;
    while (!valid) {
        cout << "\nCode of Student: ";
        cin >> student_code;
        cout << "Code of UC: ";
        cin >> uc_code;
        bool valid_s = false;
        for (Student s: v)
            if (s.get_StudentCode() == student_code) {
                valid_s = true;
                break;
            }
        bool valid_uc = false;
        for (UC uc: v_uc)
            if (uc.get_UcCode() == uc_code) {
                valid_uc = true;
                break;
            }
        if(valid_s && valid_uc) valid = true;

        if (!valid) cout << "\nInvalid code of Student or code of UC.\n";

        bool is_in_uc = false;
        for (Student s: v) {
            if (s.get_StudentCode() == student_code) {
                for (Lecture l: s.get_Schedule()) {
                    if (l.get_UcCode() == uc_code) {
                        is_in_uc = true;
                    }
                }
                break;
            }

        }
        if (!is_in_uc) {
            cout << "\nStudent is not registered in UC " << uc_code << '.' << endl;
            valid=false;
        }
    }
    remove_s(v,v_uc,v_class,student_code,uc_code);
    history.push("Student "+ student_code + " was removed from UC " + uc_code);
    vectors a;
    a.v_students_classes= v;
    a.v_classes_per_uc=v_uc;
    a.v_lectures_per_class=v_class;
    current_data.push(a);
}

/**
 * Function to switch a UC of a student.
 *
 * Use of functions add and remove.
 * Function complexity:  O(n) where 'n' is the number of Student objects in the v vector.
 *
 * @param v current vector of Students
 * @param v_uc current vector of UCs
 * @param v_class current vector of Classes
 */
void switch_UC(vector<Student>& v,vector<UC>& v_uc,vector<Class>& v_class,stack<vectors>& current_data,stack<string>& history)
{
    string student_code;
    string old_uc;
    string new_uc;
    bool valid = false;
    while (!valid) {
        cout << "\nCode of Student: ";
        cin >> student_code;
        cout << "Code of current UC: ";
        cin >> old_uc;
        cout << "Code of new UC: ";
        cin >> new_uc;
        bool valid_s=false;

        for (Student s: v)
        {
            if (s.get_StudentCode() == student_code) {
                valid_s = true;
                break;
            } else valid_s=false;
        }
        bool valid_olduc=false;
        bool valid_newuc=false;
        for (UC uc: v_uc) {
            if (uc.get_UcCode() == old_uc) {
                valid_olduc = true;
                break;
            } else valid_olduc = false;
        }
        for (UC uc: v_uc) {
            if (uc.get_UcCode() == new_uc) {
                valid_newuc = true;
                break;
            } else valid_newuc = false;
        }
        if(valid_s && valid_newuc && valid_olduc) valid=true;
        if (!valid) cout << "\nInvalid code of Student or code of UC.\n";
        for (Student s: v) {
            if (s.get_StudentCode() == student_code) {
                for (Lecture l: s.get_Schedule()) {
                    if (l.get_UcCode() == new_uc) {
                        cout << "\nStudent is already registered in UC " << new_uc << '.' << endl;
                        valid = false;
                        break;
                    }
                }
            }
        }
        bool is_in_uc = false;
        for (Student s: v) {
            if (s.get_StudentCode() == student_code) {
                for (Lecture l: s.get_Schedule()) {
                    if (l.get_UcCode() == old_uc) {
                        is_in_uc = true;
                    }
                }
                break;
            }

        }
        if (!is_in_uc) {
            cout << "\nStudent is not registered in UC " << old_uc << '.' << endl;
            valid=false;
        }

    }

    remove_s(v,v_uc,v_class,student_code,old_uc);
    add_s(v,v_uc,v_class,student_code,new_uc);
    history.push("Student "+ student_code + " switched from UC " + old_uc+ " to "+ new_uc);
    vectors a;
    a.v_students_classes= v;
    a.v_classes_per_uc=v_uc;
    a.v_lectures_per_class=v_class;
    current_data.push(a);
}

/**
 * Function to switch a class of a student.
 *
 * In order to switch a class, the new class must:
 * have a vacancy;
 * not overlap TP or PL lectures of the student;
 * improve or maintain balance of class occupation.
 * Function complexity:  O(n) where 'n' is the number of Student objects in the v vector.
 *
 * @param v current vector of Students
 * @param v_uc current vector of UCs
 * @param v_class current vector of Classes
 */
void switch_class(vector<Student>& v,vector<UC>& v_uc,vector<Class>& v_class,stack<vectors>& current_data,stack<string>& history)
{
    string student_code;
    string uc_code;
    string old_class;
    string chosen_class;
    while (true) {
        cout << "\nCode of Student: ";
        cin >> student_code;
        cout << "Code of UC: ";
        cin >> uc_code;
        cout << "\nCurrent class: ";
        cin >> old_class;
        cout << "New class: ";
        cin >> chosen_class;
        bool s_valid=false;
        bool uc_valid=false;
        bool old_valid=false;
        bool new_valid=false;
        for (Student s: v)
        {
            if (s.get_StudentCode() == student_code) {
                s_valid=true;
                break;
            }
        }

        for (UC uc: v_uc)
        {
            if (uc.get_UcCode() == uc_code) {
                uc_valid=true;
                break;
            }
        }
        for(Class c: v_class)
        {
            if (c.get_ClassCode() == old_class) {
                old_valid=true;
            }
            if (c.get_ClassCode() == chosen_class) {
                new_valid=true;
            }
        }

        if(s_valid && uc_valid && old_valid && new_valid) break;
        else
        {
            cout << "\nInvalid code of Student or code of UC.\n";
            continue;
        }
    }
    if(num_students_per_UC_class(uc_code,chosen_class,v)>=26) cout << "\nOperation not possible - the class is full\n";

        vector<Lecture> old_sch;
        for (Student s: v)
        {
            if (s.get_StudentCode()==student_code)
            {
                for (Lecture l: s.get_Schedule())
                {
                    if (l.get_UcCode() == uc_code)
                    {
                        old_class = l.get_ClassCode();
                    }
                    else if (l.get_UcCode() != uc_code)
                    {
                        old_sch.push_back(l);
                    }
                }
            }
        }
        bool no_ov=true;
        for(Class cl: v_class)
        {
            if(cl.get_ClassCode()==chosen_class)
            {
                for(Lecture l:cl.get_Schedule())
                {
                    if(l.get_UcCode()==uc_code)
                    {
                        for(Lecture l_s:old_sch)
                        if(overlap(l,l_s))
                        no_ov = false;
                        break;
                    }
                }
            }
        }
        if(!no_ov)
        {
            cout << "\nOperation not possible - there is class overlap.\n";
            return;
        }
        for (Class cl: v_class) {
            if (cl.get_ClassCode()==chosen_class)
            {
                for (Lecture lec:cl.get_Schedule())
                {
                    if (lec.get_UcCode()==uc_code)
                    {
                        old_sch.push_back(lec);
                    }
                }
            }
        }

        for (Student& s: v)
        {
            if (s.get_StudentCode()==student_code)
            {
                s.set_Schedule(old_sch);
                break;
            }
        }
    history.push("Student "+ student_code + " switched from class " + old_class+ " to "+ chosen_class);
    vectors a;
    a.v_students_classes= v;
    a.v_classes_per_uc=v_uc;
    a.v_lectures_per_class=v_class;
    current_data.push(a);
    cout << "\nRequest accepted :)";

}

/**
 * Function to undo a request in the history.
 * Function complexity: O(1)
 * @param data_history Stack with updated data structures
 * @param history Stack with requests history
 * @param v current vector of Students
 * @param v_uc current vector of UCs
 * @param v_class current vector of Classes
 */
void go_back(stack<vectors>& data_history,stack<string>& history,vector<Student>& v,vector<UC>& v_uc,vector<Class>& v_class)
{

    if(history.empty())return;
    data_history.pop();
    history.pop();
    if(!history.empty())
    {
        vectors a = data_history.top();
        v = a.v_students_classes;
        v_uc = a.v_classes_per_uc;
        v_class = a.v_lectures_per_class;
    }
    else return;

}

