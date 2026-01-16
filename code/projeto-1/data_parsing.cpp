#include "data_parsing.h"


/**
 * Parsing function of the csv file containing all the lectures.
 *
 * @return vector of Lectures (one lecture per line of file).
 */
vector<Lecture> parsing_classes() {
    vector<Lecture> v;
    string line;
    ifstream f_classes("classes.csv");
    Lecture c;
    getline(f_classes, line); //Ignores first line (header)
    while (getline(f_classes, line))
    {
            istringstream iss(line);
            string ClassCode_,UcCode_,Weekday_,StartHour_string_,Duration_string_,Type_;

            getline(iss, ClassCode_, ',');
            getline(iss, UcCode_, ',');
            getline(iss, Weekday_, ',');
            getline(iss, StartHour_string_, ',');
            getline(iss, Duration_string_, ',');
            float StartHour_ = stof(StartHour_string_);
            float Duration_ = stof(Duration_string_);
            iss >> Type_;

            c.set_ClassCode(ClassCode_);
            c.set_UcCode(UcCode_);
            c.set_Weekday(Weekday_);
            c.set_StartHour(StartHour_);
            c.set_Duration(Duration_);
            c.set_Type(Type_);
            v.push_back(c);
    }

    return v;
}

/**
 * Parsing function of the csv file containing students and their class per UC.
 * In this csv file, the information of every student is in consecutive lines.
 * Therefore, the information of every student is gathered until the student changes.
 *
 * @return vector of Students with their corresponding schedule.
 */
vector<Student> parsing_students_classes() {
    vector<Student> students;
    vector<Lecture> classes = parsing_classes();

    ifstream file("students_classes.csv");
    string line;
    string prevStudentCode = "";
    string currentStudentCode;
    string currentStudentName;
    vector<Lecture> studentSchedule;

    getline(file, line); // Ignores first line (header)

    while (getline(file, line)) {
        istringstream iss(line);

        string StudentCode, StudentName, UcCode, ClassCode;
        getline(iss, StudentCode, ',');
        getline(iss, StudentName, ',');
        getline(iss, UcCode, ',');
        iss >> ClassCode;

        if (StudentCode != prevStudentCode) {
            if (!prevStudentCode.empty()) {
                // Create a Student object for the previous student
                Student student(prevStudentCode, currentStudentName, studentSchedule);
                students.push_back(student);
            }

            // Reset data for the new student
            prevStudentCode = StudentCode;
            currentStudentName = StudentName;
            studentSchedule.clear();
        }


        for (Lecture aClass : classes) {
            if (UcCode == aClass.get_UcCode() && ClassCode == aClass.get_ClassCode()) {
                studentSchedule.push_back(aClass);
            }
        }
    }

    // Create a Student object for the last student in the file
    if (!prevStudentCode.empty()) {
        Student student(prevStudentCode, currentStudentName, studentSchedule);
        students.push_back(student);
    }

    return students;
}


/**
 *Function that organizes the information of the existing Lectures in Class objects.
 *
 * @param v_lectures vector of Lectures returned in the parsing_classes function.
 * @return vector of Classes and their corresponding schedule.
 */
vector<Class> lectures_per_class(vector<Lecture>& v_lectures)
{
    vector<Class> v;
    Class c;
    set<string> classCodes;
    vector<Lecture> v_;
    for(Lecture l: v_lectures)
    {
        classCodes.insert(l.get_ClassCode());
    }
    for(string s: classCodes)
    {

        for(Lecture l: v_lectures)
        {
            if (s == l.get_ClassCode())
            {
                v_.push_back(l);
            }
        }
        c.set_ClassCode(s);
        sort(v_.begin(),v_.end(), [](Lecture a, Lecture b)
        {
            return (a.get_StartHour()<b.get_StartHour());
        });
        c.set_Schedule(v_);
        v.push_back(c);
        v_.clear();
    }

    return v;
}

/**
 * Parsing function of the csv file containing one UC and one corresponding class.
 *
 * @return vector of UCs with their corresponding classes.
 */
vector<UC> parsing_classes_per_uc() {

    vector<vector<string>> v;
    vector<string> v1;
    ifstream f_classesperuc("classes_per_uc.csv");
    string line;
    getline(f_classesperuc, line); //Ignores first line of csv file (header)
    while (getline(f_classesperuc, line)) {
        istringstream iss(line);

        string UcCode_, ClassCode_;
        getline(iss, UcCode_, ',');
        iss >> ClassCode_;

        v1 = {UcCode_, ClassCode_};
        v.push_back(v1);
    }

    string uc_code= v[0][0];
    vector<string> v_classes;
    UC uc;
    vector<UC> v_uc;
    int last = v.size();
    last--;
    for(vector<string> vector:v)
    {
        if(uc_code==vector[0])
        {
            v_classes.push_back(vector[1]);
        }
        else
        {
            uc.set_UcCode(uc_code);
            uc.set_ClassCodes(v_classes);
            v_uc.push_back(uc);
            uc_code = vector[0];
            v_classes.clear();
        }
        //last UC:
        if (vector==v[last])
        {
            uc.set_UcCode(uc_code);
            uc.set_ClassCodes(v_classes);
            v_uc.push_back(uc);
            uc_code = vector[0];
            v_classes.clear();
        }
    }

    return v_uc;
}



