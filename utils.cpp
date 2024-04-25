#include <string>
#include "utils.h"
using namespace std;

string Utils::RemoveSpace(const char* str) {
    string inp(str);
    inp.erase(remove_if(inp.begin(), inp.end(), ::isspace), inp.end());
    return inp;
}