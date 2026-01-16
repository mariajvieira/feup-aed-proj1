#include "data_parsing.h"
#include "consult_functions.h"
#include "requests_functions.h"
#include <stack>

/**
 * Function of the Schedule Manager menu.
 * This is a user-friendly program that allows the user to choose the commands and go back to the menu at any time.
 *
 */
int main() {
    vector<Lecture> v_classes = parsing_classes();

    vector<Student> v_students_classes = parsing_students_classes();

    vector<Class> v_lectures_per_class = lectures_per_class(v_classes);

    vector<UC> v_classes_per_uc = parsing_classes_per_uc();

    stack<vectors> current_data;
    stack<string> history;


        while (true) {
            //system("clear");
            cout << "\nWelcome to Schedule Manager!\n\n"
                 << "1 -> Consult students\n"
                 << "2 -> Consult number of students registered in at least n UCs\n"
                 << "3 -> Consult numbers of students in UCs\n"
                 << "4 -> Check schedule\n"
                 << "5 -> Request change\n"
                 << "6 -> Consult request history\n"
                 << "7 -> Exit Schedule Manager\n"
                 << "\nChoose one of the above: ";

            int option;
            cin >> option;
            cin.ignore();
            //system("clear");

            if(option==1) {
                uc_class_student(v_classes_per_uc, v_students_classes);
                continue;
            }
            else if(option ==2)
            {
                print_students_registered_in_at_least_n_UCs(v_students_classes);
                continue;
            }
            else if (option == 3)
            {
                print_num_students_per_uc(v_students_classes);
                cout << "\n(enter 'q' to return to menu)\n";
                char c;
                cin >> c;
                if(c=='q') continue;
            }
            else if ( option == 4)
            {
                cout << "Check schedule of:\n"
                        "\n1 -> Student"
                        "\n2 -> Class\n"
                        "\n(enter 'q' to return to menu)\n"
                        "\nChoose one of the above: ";
                string input;
                while (true) {
                    cin >> input;
                    cin.ignore();
                    //system("clear");
                    if (input == "1") {
                        print_student_schedule(v_students_classes);
                        cout << "\n(enter 'q' to return to menu)\n";

                    } else if (input == "2") {
                        print_class_schedule(v_lectures_per_class);
                        cout << "\n(enter 'q' to return to menu)\n";
                    } else if (input == "q") {
                        //system("clear");
                        break;

                    }
                    else cout << "Invalid input, try again: ";
                }
                continue;

            }
            else if(option == 5) {
                cout << "1 -> Add UC\n"
                        "2 -> Remove UC\n"
                        "3 -> Switch UC\n"
                        "4 -> Switch Class\n"
                        "\n (enter 'q' to return to menu)\n"
                        "\nChoose one of the above: ";
                bool menu= false;
                string input;
                while (true) {
                    cin >> input;
                    cin.ignore();
                    //system("clear");
                    if (input == "1") {
                        add_to_UC(v_students_classes, v_classes_per_uc, v_lectures_per_class,current_data,history);
                        cout << "\nRequest accepted :)"
                             << "\nTo consult the updated schedule of the student go to Menu-> Check schedule -> Student.\n"
                             << "\n(enter 'q' to return to menu)\n";
                    } else if (input == "2") {
                        remove_from_UC(v_students_classes, v_classes_per_uc, v_lectures_per_class,current_data,history);
                        cout << "\nRequest accepted :)"
                             << "\nTo consult the updated schedule of the student go to Menu-> Check schedule -> Student.\n"
                             << "\n(enter 'q' to return to menu)\n";
                    } else if (input == "3") {
                        switch_UC(v_students_classes, v_classes_per_uc, v_lectures_per_class,current_data,history);
                        cout << "\nRequest accepted :)"
                             << "\nTo consult the updated schedule of the student go to Menu-> Check schedule -> Student.\n"
                             << "\n(enter 'q' to return to menu)\n";
                    } else if (input == "4") {
                        switch_class(v_students_classes, v_classes_per_uc, v_lectures_per_class,current_data,history);
                        cout << "\nTo consult the updated schedule of the student go to Menu-> Check schedule -> Student.\n"
                             << "\n(enter 'q' to return to menu)\n";
                    }
                    else if (input == "q") {
                            //system("clear");
                            break;
                    }
                    else cout << "Invalid input, try again: ";
                }
                continue;
            }
            else if(option==6) {
                consult_history(history);
                while (true)
                {
                    cout << "\nTo undo a change enter 'u'\n"
                    << "(to go back to menu enter 'q')";
                    char c;
                    cin >> c;
                    if (c == 'u')
                    {
                        //system("clear");
                        go_back(current_data, history,v_students_classes,v_classes_per_uc,v_lectures_per_class);
                        consult_history(history);
                    }
                    else if (c == 'q')
                    {
                        break;
                    }
                    else continue;
                }
                continue;

            }
            else if(option==7) {
                //system("clear");
                return 0;
            }
            else
            {
                cout<< "Invalid input, try again: ";
                continue;
            }
        }
        return 0;
    }
