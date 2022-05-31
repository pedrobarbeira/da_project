//
// Created by pbarbeira on 31-05-2022.
//

#ifndef DA_PROJECT_CASE2_H
#define DA_PROJECT_CASE2_H

#include "utils.h"
#include "graph.h"

void case_2_1(Graph& gaph){
    int src, dest, size;
    std::cout << "### Case 1.2 ###\n";
    while (1) {
        std::cout << "Source: ";
        std::cin >> src;
        if (src <= 0 || src > graph.size()) std::cout << "Invalid source\n";
        else break;
    }
    while (1) {
        std::cout << "Dest: ";
        std::cin >> dest;
        if (dest <= 0 || dest > graph.size()) std::cout << "Invalid dest\n";
        else break;
    }
    while (1) {
        std::cout << "Group size: ";
        std::cin >> size;
        if (size <= 0) sd::cout << "Invalid size\n";
        else break;
    }

}

#endif //DA_PROJECT_CASE2_H
