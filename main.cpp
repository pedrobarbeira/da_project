#include <iostream>
#include "case1.h"
#include "case2.h"
#include "caseJ.h"
#include "testfulkerson.h"
#include "paretograph.h"



int main() {
    int opt;
    while(1){
        std::cout << "[1] Case 1\n[2] Case 2\n\n[0] Exit\n$";
        std::cin>>opt;
        switch(opt){
            case 1: case_1();
            case 2: case_2();
            case 0: exit(0);
            default: std::cout << "Invalid option";
        }
    }

    return 0;

}
