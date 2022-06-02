//
// Created by pbarbeira on 31-05-2022.
//

#ifndef DA_PROJECT_CASE2_H
#define DA_PROJECT_CASE2_H

#include "utils.h"
#include "fulkersongraph.h"

void case_2_1(){
    int dataSet;
    while (1) {
        std::cout << "Choose Data Set [0-10]: ";
        std::cin >> dataSet;
        if (dataSet < 0 || dataSet > 10) std::cout << "Invalid Data Set\n";
        else break;
    }
    string fpath = get_fpath(dataSet);
    FulkersonGraph graph = FulkersonGraph(fpath);
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
        if (size <= 0) std::cout << "Invalid size\n";
        else break;
    }
    std::vector<std::pair<int, std::vector<int>>> paths;
    std::pair<int, std::vector<int>> path;
    bool flag = false;
    while (size > 0){
        graph.max_capacity_min_dist(src);
        path = graph.retrieve_path(src, dest);
        if(path.second.empty()){
            flag = true;
            break;
        }
        size -= path.first;
        paths.push_back(path);
    }
    std::cout << "\n## Paths ##";
    if(flag){
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
