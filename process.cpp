#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "process.h"
#include "utils.h"
#include "display.h"

using namespace std;



void processFollowUp(int inCmdType, string secondArg){

    string line;
    ifstream fin;
    ofstream fout;
    
    try{

        switch(inCmdType){
            case static_cast<int>(Process::list_of_commands::READ_FILE):
                {
                    cout << " opening " << secondArg << "\n";
                    fin.open(secondArg);

                    if(!fin.is_open()) {
                        fin.close();
                        throw runtime_error("failed to open the file");
                    } 
                    cout << " reading " << secondArg << "\n";
                    while(getline(fin, line)){
                        cout << line << "\n";
                    }
                    cout << " closing " << secondArg << "\n";
                    fin.close();
                }
                break;

            case static_cast<int>(Process::list_of_commands::WRITE_FILE):
                {
                    cout << " opening " << secondArg << "\n";
                    fout.open(secondArg);

                    if(!fout.is_open()){
                        fout.close();
                        throw runtime_error("failed to open the file");
                    } 
                    cout << "start writing to file, stop anytime by entering -1" << "\n";

                    while(fout){
                        getline(cin, line);

                        if(line == "-1") break;

                        fout << line << "\n";
                    }

                    cout << " closing " << secondArg << "\n";
                    fout.close();
                }
                break;
            
            default:
                break;
        }
    } catch (const exception& e){
        cerr << "Error: " << e.what() << "\n";
    }
}



string processArg(const char* str){
    cout << "processing argument..." << "\n";
    string result = Utils::RemoveSpace(str);

    for(char& c : result) c = ::tolower(c);

    return result;
}



void Process::AllArgs(int argc, char* argv[]){
    list_of_commands cmd; { list_of_commands::INVALID;}

    // string temp = Utils::RemoveSpace(argv[1]);
    // for_each(temp.begin(), temp.end(), [](char& i) {
    //     i = ::tolower(i);
    // });

    string temp = processArg(argv[1]);

    if(temp == "-a" || temp == "-archive"){
        cmd = list_of_commands::READ_FILE;
    } else if(temp == "-x" || temp == "-unarchive"){
        cmd = list_of_commands::WRITE_FILE;
    }

    switch(static_cast<int>(cmd)){
        case static_cast<int>(list_of_commands::INVALID):
            Display::Help();
            break;
        case static_cast<int>(list_of_commands::READ_FILE):
        case static_cast<int>(list_of_commands::WRITE_FILE):
            { 
                string temp2 = processArg(argv[2]);
                processFollowUp(static_cast<int>(cmd), temp2);
            }
            break;
        default:
            break;
        
    }

}