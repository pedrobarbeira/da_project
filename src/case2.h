//
// Created by pbarbeira on 31-05-2022.
//

#ifndef DA_PROJECT_CASE2_H
#define DA_PROJECT_CASE2_H

#include "utils.h"
#include "graph.h"
#include "fulkersongraph.h"

void case_2_1(){
    /*int dataSet;
    while (1) {
        std::cout << "Choose Data Set [0-10]: ";
        std::cin >> dataSet;
        if (dataSet < 0 || dataSet > 10) std::cout << "Invalid Data Set\n";
        else break;
    }*/
    string fpath = TEST_SET_2;
    FulkersonGraph graph = FulkersonGraph(DATA_SET_2);
    int src, dest, size;
    std::cout << "### Case 2.1 ###\n";
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
        if (size <= 0) std::cout << "Invalid size\n";
        else break;
    }
    std::vector<std::pair<int, std::vector<int>>> paths;
    graph.ford_fulkerson(src, dest, size, paths);
    std::cout << "\n## Paths ##";
    int count = 0;
    for(auto p : paths){
        count += p.first;
    }
    if(count < size){
        std::cout << "\n--------------\n"
                  << "Unfortunately there are no paths for your group\n(you'll have to walk)";
        return;
    }
    else {
        for (auto v: paths) {
            std::cout << "\n--------------"
                      << "\nCapacity: " << v.first
                      << "\nPath: (";
            for (int i = v.second.size() - 1; i >= 0; i--) {
                if (i == 0) std::cout << v.second[i] << ")";
                else std::cout << v.second[i] << "->";
            }
        }
        std::cout << "\n--------------";
    }
}

#endif //DA_PROJECT_CASE2_H
