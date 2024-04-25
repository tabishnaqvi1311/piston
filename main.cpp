#include <iostream>
#include "display.h"
#include "process.h"
using namespace std;

int main(int argc, char *argv[]){

    if(argc <= 1) Display::Help();

    else Process::AllArgs(argc, argv);

    return 0;
}