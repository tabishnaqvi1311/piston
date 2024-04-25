#pragma once
#include <string>
using namespace std;

namespace Process {
    enum class list_of_commands {
        INVALID,
        READ_FILE,
        WRITE_FILE
    };

    void AllArgs(int argc, char *argv[]);
}