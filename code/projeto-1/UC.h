#ifndef SCHEDULE_UC_H
#define SCHEDULE_UC_H
#include <string>
#include <vector>
using namespace std;

class UC {

private:
    string UcCode;
    vector<string> ClassCodes;

public:

    UC();
    UC(string a, vector<string> b);
    void set_UcCode(string a);
    void set_ClassCodes(vector<string> a);
    string get_UcCode();
    vector<string> get_ClassCodes();
    void add_UcClass(string ucclass);
};


#endif //SCHEDULE_UC_H