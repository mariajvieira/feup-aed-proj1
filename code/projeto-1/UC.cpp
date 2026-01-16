#include "UC.h"

UC::UC(): UcCode("UcCode"), ClassCodes({" "}) {}
UC::UC(string a, vector<string> b): UcCode(a), ClassCodes(b) {}
void UC::set_UcCode(string a) {
    UcCode = a;
}
void UC::set_ClassCodes(vector<string> a) {
    ClassCodes = a;
}
string UC::get_UcCode() {
    return UcCode;
}
vector<string> UC::get_ClassCodes() {
    return ClassCodes;
}
void UC::add_UcClass(string ucclass) {
    ClassCodes.push_back(ucclass);
}