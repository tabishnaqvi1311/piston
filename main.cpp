#include <iostream>
#include "display.h"
#include "process.h"
using namespace std;

int main(int argc, char *argv[]){

    if(argc != 3) Display::Help();

    Process::AllArgs(argc, argv);

    return 0;
}