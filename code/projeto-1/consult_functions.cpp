#include "consult_functions.h"

void print_student_schedule(vector<Student> v)
{
    string code;
    cout << "Code of Student: ";
    cin >> code;
    cout << endl;
    vector<string> week= {"Monday","Tuesday","Wednesday","Thursday","Friday"};
    bool student_exists = false;
    for(Student s : v)
    {
        if(s.get_StudentCode() == code)
        {
            student_exists = true;
            for(string weekday: week)
            {
                bool has_class_that_day = false;
                cout << weekday <<':' << endl << endl;
                for(Lecture c: s.get_Schedule()) {
                    if (weekday == c.get_Weekday()) {
                        has_class_that_day = true;
                        int a = c.get_StartHour() * 10.0;
                        int b = c.get_Duration() * 10.0;
                        int d = a + b;
                        if ((a%10==5)&&(d%10==5))
                            cout << a/10 << ":" << "30H" << '-'<< d/10 << ":" << "30H";
                        else if ((a%10==0)&&(d%10==0))
                            cout << a/10 << ":" << "00H" << '-'<< d/10 << ":" << "00H";
                        else if ((a%10==5)&&(d%10==0))
                            cout << a/10 << ":" << "30H" << '-'<< d/10 << ":" << "00H";
                        else if ((a%10==0)&&(d%10==5))
                            cout << a/10 << ":" << "00H" << '-'<< d/10 << ":" << "30H";

                        cout<< endl << "UC: " << c.get_UcCode() << "(" << c.get_Type() << ")\n" <<
                        "Class: " << c.get_ClassCode() << endl<<endl;
                    }
                }
                if(!has_class_that_day) cout << "No Classes\n";
                cout << endl;
            }
        }
    }
    if(!student_exists) cout << "Invalid Code of Student.\n";
}

void print_class_schedule(vector<Class> v)
{
    string code;
    cout << "Code of Class: ";
    cin >> code;
    cout << endl;
    vector<string> week= {"Monday","Tuesday","Wednesday","Thursday","Friday"};
    bool class_exists = false;
    for(Class c : v) {
        if (c.get_ClassCode() == code) {
            class_exists = true;
            for (string weekday: week) {
                bool has_class_that_day = false;
                cout << weekday <<':' << endl << endl;
                for (Lecture l: c.get_Schedule()) {
                    if (l.get_Weekday() == weekday) {
                        has_class_that_day = true;
                        int a = l.get_StartHour() * 10.0;
                        int b = l.get_Duration() * 10.0;
                        int d = a + b;
                        if ((a%10==5)&&(d%10==5))
                            cout << a/10 << ":" << "30H" << '-'<< d/10 << ":" << "30H";
                        else if ((a%10==0)&&(d%10==0))
                            cout << a/10 << ":" << "00H" << '-'<< d/10 << ":" << "00H";
                        else if ((a%10==5)&&(d%10==0))
                            cout << a/10 << ":" << "30H" << '-'<< d/10 << ":" << "00H";
                        else if ((a%10==0)&&(d%10==5))
                            cout << a/10 << ":" << "00H" << '-'<< d/10 << ":" << "30H";

                        cout<< endl << "UC: " << l.get_UcCode() << "(" << l.get_Type() << ")\n" <<
                            "Class: " << c.get_ClassCode() << endl<<endl;
                    }
                }
                if (!has_class_that_day) cout << "No Lectures\n";
                cout << endl;
            }
        }
    }
    if(!class_exists) cerr << "Invalid Code of Class.\n";
}

void print_students_given_class(vector<Student> v)
{
    string code;
    cout << "Code of Class: ";
    cin >> code;
    cout << endl;
    set<pair<string, string>> set_students;

    for(Student s: v)
    {
        for (Lecture l: s.get_Schedule())
        {
            if (l.get_ClassCode()==code)
            {
                pair<string, string> p;
                p.first=s.get_StudentName();
                p.second=s.get_StudentCode();
                set_students.insert(p);
            }
        }
    }
    if(set_students.size()==0) cout << "Invalid Code of UC.\n";
    for (pair<string,string> p: set_students)
    {
        cout << p.second << " - "<< p.first << endl;
    }
}

void print_students_given_course(vector<Student> v)
{
    string code;
    cout << "Code of UC: ";
    cin >> code;
    cout << endl;
    set<pair<string, string>> set_students;
    for(Student s: v)
    {
        for (Lecture l: s.get_Schedule())
        {
            if (l.get_UcCode()==code)
            {
                pair<string, string> p;
                p.first=s.get_StudentName();
                p.second=s.get_StudentCode();
                set_students.insert(p);
            }
        }
    }
    if(set_students.size()==0) cout << "Invalid Code of UC.\n";

    for (pair<string,string> p: set_students)
    {
        cout << p.second << " - "<< p.first << endl;
    }

}

void print_students_given_year(vector<Student> v)
{
    char year;
    cout << "Year: ";
    cin >> year;
    cout << endl;
    if (int(year)<1 || int(year)>3)
    {
        cout << "Invalid year. Choose 1, 2 or 3.\n";
        return;
    }
    cout << endl;
    set<pair<string, string>> set_students;
    for(Student s: v)
    {
        for (Lecture l: s.get_Schedule())
        {
            if (l.get_ClassCode()[0]==year)
            {
                pair<string, string> p;
                p.first=s.get_StudentName();
                p.second=s.get_StudentCode();
                set_students.insert(p);
            }
        }
    }

    for (pair<string,string> p: set_students)
    {
        cout << p.second << " - "<< p.first << endl;
    }
}

void print_students_registered_in_at_least_n_UCs(vector<Student> v)
{
    int n;
    cout << "Number of UCs: ";
    cin >> n;
    cout << endl;
    set<string> set_UCs;
    int num_students=0;
    for(Student s: v)
    {
        for (Lecture l: s.get_Schedule())
        {
            set_UCs.insert(l.get_UcCode());
        }
        if(set_UCs.size()>=n)
        {
            num_students++;
        }
        set_UCs.clear();
    }
    if (num_students==0) cout<< "No student is registered in at least "<< n << " UCs.\n";
    else cout << "The number of students registered in at least " << n << " UCs is " << num_students << ".\n";

}

void print_num_students_per_uc(vector<Student> v)
{
    set<string> set_UCs;
    vector<set<string>> v_set;

    for(Student s: v)
    {
        for (Lecture l: s.get_Schedule())
        {
            set_UCs.insert(l.get_UcCode());
        }
    }

vector<pair<int,string>> v_uc_num;
    int counter=0;
    for(string uc:set_UCs)
    {
        for(Student s: v)
        {
            for (Lecture l: s.get_Schedule())
            {
                if(l.get_UcCode() == uc)
                {
                    counter ++;
                }
            }
        }
        pair<int,string> p;
        p.first = counter;
        p.second = uc;
        v_uc_num.push_back(p);
        counter=0;
    }
    sort(v_uc_num.begin(),v_uc_num.end(),[](pair<int,string>a,pair<int,string>b){return a.first>b.first;});
    cout << endl<< "Code of UC:     Number of students:\n";
    for(pair<int,string> pair: v_uc_num)
    {
        cout <<" "<<  pair.second << " ----------> " << pair.first<< endl;
    }
}

void num_students_per_class(vector<UC> v_uc, vector<Student> v_stu)
{
    set<string> set_Classes;
    for(UC uc: v_uc)
    {
        for (string c: uc.get_ClassCodes())
        {
            set_Classes.insert(c);
        }
    }

    vector<pair<int,string>> v_class_num;
    int counter=0;
    for(string c:set_Classes)
    {
        for(Student s: v_stu)
        {
            for (Lecture l: s.get_Schedule())
            {
                if(l.get_ClassCode() == c)
                {
                    counter ++;
                    break;
                }
            }
        }
        pair<int,string> p;
        p.first = counter;
        p.second = c;
        v_class_num.push_back(p);
        counter=0;
    }
    sort(v_class_num.begin(),v_class_num.end(),[](pair<int,string>a,pair<int,string>b){return a.first>b.first;});
    cout << endl<< "Code of Class:     Number of students:\n";
    for(pair<int,string> pair: v_class_num)
    {
        cout <<" "<<  pair.second << " ----------> " << pair.first<< endl;
    }

}

void num_students_class_per_uc(vector<UC> v_uc, vector<Student> v) {
    string code;
    cout << "Code of UC: ";
    cin >> code;
    cout << endl;
    set<string> set_Classes;
    for(UC uc: v_uc)
    {
        for (string c: uc.get_ClassCodes())
        {
            set_Classes.insert(c);
        }
    }
    set<pair<string, string>> set_students;
    for (string c: set_Classes) {
        //cout << c << endl;
        for (Student s: v) {
            for (Lecture l: s.get_Schedule()) {

                if (l.get_UcCode() == code && l.get_ClassCode() ==c)
                {
                    pair<string, string> p;
                    p.first = s.get_StudentName();
                    p.second = s.get_StudentCode();
                    set_students.insert(p);
                }
            }
        }
    }
    if(set_students.size()==0) cerr << "Invalid Code of UC.\n";

    for (pair<string,string> p: set_students)
    {
        cout << p.second << " - "<< p.first << endl;
    }
}

/**
 * Function that shows students of a chosen year, uc and class.
 * Function complexity: (O(m * n)) where 'm' is the number of UC objects, and 'n' is the average number of class codes or lectures.
 * @param v_uc current vector of UCs
 * @param v current vector of Students
 */
void uc_class_student(vector<UC> v_uc, vector<Student> v)
{
    set<string> set_UC;
    cout << "\n1 Year\n" << "2 Year\n" << "3 Year\n";
    cout << "\nChoose a year to consult UCs (write the number of the year):"<<endl;
    string num_year;
    set<string> y= {"1","2","3"};
    bool year_is_in_set=false;
    while (true)
    {
        cin >> num_year;
        for(string year:y)
        {
            if(year==num_year) year_is_in_set=true;
        }
        if(year_is_in_set) break;
        else
        {
            cout << "\nInvalid year. Please choose a year from the list above! ";
            continue;
        }
    }

    //system("clear");
    cout <<"\nCourse Units:\n\n";
    for(UC uc:v_uc)
    {
        for(string s: uc.get_ClassCodes()) {
            if (s[0] == num_year[0])
                set_UC.insert(uc.get_UcCode());
            break;
        }
    }
    for(string uc:set_UC)cout << uc << endl;

    cout << "\nChoose a UC to consult classes (write the code of the UC): ";
    string uc_code;

    bool is_in_set=false;
    while (true)
    {
        cin >> uc_code;
        for(string s:set_UC)
        {
            if(s==uc_code)
            {
                is_in_set=true;
            }
        }
        if(is_in_set) break;
        else
        {
            cout << "\nInvalid UC. Please choose a UC from the list above! ";
            continue;
        }
    }

    set<string> set_Classes;
    for(UC uc: v_uc)
    {
        if(uc.get_UcCode()==uc_code) {
            for (string c: uc.get_ClassCodes()) {
                set_Classes.insert(c);
            }
        }
    }
    //system("clear");
    cout <<"\nClasses of " << uc_code <<":\n\n";
    for(string s: set_Classes) cout << s<<endl;
    cout << "\nChoose a Class to consult students (write the code of the class):"<<endl;
    string class_code;
    cin >> class_code;
    set<pair<string,string>> set_student;
    for(Student s : v)
    {
        for(Lecture l: s.get_Schedule())
        {
            if(l.get_UcCode()==uc_code && l.get_ClassCode()== class_code)
            {
                pair<string,string> p;
                p.first = s.get_StudentName();
                p.second = s.get_StudentCode();
                set_student.insert(p);
            }
        }
    }
    //system("clear");
    if (set_student.size()==0) cout << "\nNo students in this class!\n";
    else
    {
        cout <<"\nStudents of " << class_code <<":\n\n";
        for(pair<string,string> p: set_student)
        {
            cout << p.second << " - " << p.first << endl;
        }
    }

}


/**
 * Function to consult the requests history.
 * Function complexity: O(n) where 'n' is the number of elements in the history stack.
 * @param history Stack of the requests made
 */
void consult_history(stack<string> history)
{
    cout << "\nHistory: \n";
    if (history.empty())
    {
        cout << "\nNo changes have been made.\n";
    }
    else {

        while (!history.empty()) {
            cout << history.top() << endl;
            history.pop();

        }
    }
}

