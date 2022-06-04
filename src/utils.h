#ifndef PROJECT2_UTIL_H
#define PROJECT2_UTIL_H

#include <cmath>
#include <exception.h>
#include <fstream>
#include "graph.h"

string TEST_SET_1 = "tests/test01.txt";
string TEST_SET_2 = "tests/test03";
string DATA_SET_1 = "tests/in01.txt";
string DATA_SET_2 = "tests/in02.txt";
string DATA_SET_3 = "tests/in03.txt";
string DATA_SET_4 = "tests/in04.txt";
string DATA_SET_5 = "tests/in05.txt";
string DATA_SET_6 = "tests/in06.txt";
string DATA_SET_7 = "tests/in07.txt";
string DATA_SET_8 = "tests/in08.txt";
string DATA_SET_9 = "tests/in09_b.txt";
string DATA_SET_10 = "tests/in10_b.txt";

std::string get_fpath_1(int dataSet){
    std::string path;
    switch(dataSet) {
        case 0: path = TEST_SET_1; break;
        case 1: path = DATA_SET_1; break;
        case 2: path = DATA_SET_2; break;
        case 3: path = DATA_SET_3; break;
        case 4: path = DATA_SET_4; break;
        case 5: path = DATA_SET_5; break;
        case 6: path = DATA_SET_6; break;
        case 7: path = DATA_SET_7; break;
        case 8: path = DATA_SET_8; break;
        case 9: path = DATA_SET_9; break;
        case 10: path = DATA_SET_10; break;
        default: path = "";
    }
    return path;
}

std::string get_fpath_2(int dataSet){
    std::string path;
    switch(dataSet) {
        case 0: path = TEST_SET_2; break;
        case 1: path = DATA_SET_1; break;
        case 2: path = DATA_SET_2; break;
        case 3: path = DATA_SET_3; break;
        case 4: path = DATA_SET_4; break;
        case 5: path = DATA_SET_5; break;
        case 6: path = DATA_SET_6; break;
        case 7: path = DATA_SET_7; break;
        case 8: path = DATA_SET_8; break;
        case 9: path = DATA_SET_9; break;
        case 10: path = DATA_SET_10; break;
        default: path = "";
    }
    return path;
}

#endif //PROJECT2_UTIL_H
