#include <iostream>
#include "display.h"
using namespace std;


#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void Display::Help(){

    cout << ANSI_COLOR_CYAN 
         <<  " .S_sSSs     .S    sSSs  sdSS_SSSSSSbs    sSSs_sSSs     .S_sSSs    \n"
            " .SS~YS%%b   .SS   d%%SP  YSSS~S%SSSSSP   d%%SP~YS%%b   .SS~YS%%b   \n"
            " S%S   `S%b  S%S  d%S'         S%S       d%S'     `S%b  S%S   `S%b  \n"
            " S%S    S%S  S%S  S%|          S%S       S%S       S%S  S%S    S%S  \n"
            " S%S    d*S  S&S  S&S          S&S       S&S       S&S  S%S    S&S  \n"
            " S&S   .S*S  S&S  Y&Ss         S&S       S&S       S&S  S&S    S&S  \n"
            " S&S_sdSSS   S&S  `S&&S        S&S       S&S       S&S  S&S    S&S  \n"
            " S&S~YSSY    S&S    `S*S       S&S       S&S       S&S  S&S    S&S  \n"
            " S*S         S*S     l*S       S*S       S*b       d*S  S*S    S*S  \n"
            " S*S         S*S    .S*P       S*S       S*S.     .S*S  S*S    S*S  \n"
            " S*S         S*S  sSS*S        S*S        SSSbs_sdSSS   S*S    S*S  \n"
            " S*S         S*S  YSS'         S*S         YSSP~YSSY    S*S    SSS  \n"
            " SP          SP                SP                       SP          \n"
            " Y           Y                 Y                        Y           \n"
            "                                                   \n" << ANSI_COLOR_RESET;

    cout << "======================================================\n";

    cout << "Piston's Usage: \n"
         << " command       args                               description\n"
         << " -------       ----                               -----------\n"
         << "-p, --percent [x; where x<100]                  | Try for a % success chance. ex \"-p 50.0\"\n"
         << "-o, --odds    [x; where x<y] in [y; where y>x]  | Odds. ex \"-o 1in10\"\n"
         << "-r, --roll    [x]d[y]; where x&y are ints > 0   | Roll dice. ex \"-r 3d6\"\n";
}