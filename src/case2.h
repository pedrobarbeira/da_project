//
// Created by pbarbeira on 31-05-2022.
//

#ifndef DA_PROJECT_CASE2_H
#define DA_PROJECT_CASE2_H

#include "utils.h"
#include "graph.h"
#include "fulkersongraph.h"
#include "algorithm"

//TODO plug in dataset selection



bool shorter_time(Path* a, Path* b){
    return a->duration < b->duration;
}

void case_2() {
    int dataSet;
    while (1) {
        std::cout << "Choose Data Set [0-10]: ";
        std::cin >> dataSet;
        if (dataSet < 0 || dataSet > 10) std::cout << "Invalid Data Set\n";
        else break;
    }
    string fpath = get_fpath_2(dataSet);
    FulkersonGraph graph = FulkersonGraph(fpath);
    int src, dest, size;
    std::cout << "### Case 2 ###\n";
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
    std::vector<Path*> paths;
    graph.ford_fulkerson(src, dest);
    paths = graph.get_paths();
    std::vector<int> totalTimes;
    int maxCount = 0;
    for (auto p: paths) {
        maxCount += p->capacity;
    }
    std::cout << "\nMax Network Capacity: " << maxCount;
    if (maxCount < size) {
        std::cout << "\n--------------\n"
                  << "Your group is too large to handle\n(lose some friends, popstar)"
                  << "\n--------------\n";
        return;
    }
    bool flag = true;
    int count = 0;
    while (1) {
        std::vector<Path*>::const_iterator it;
        if (flag) {
            std::cout << "\n## Paths ##";
            int temp = 0, maxTime=0, minTime=INT32_MAX;
            for (it = paths.begin(); temp < size; it++) {
                temp += (*it)->capacity;
                std::cout << "\n--------------"
                          << "\nCapacity: " << (*it)->capacity
                          << "\nPath: (";
                for (int i = (*it)->path.size() - 1; i >= 0; i--) {
                    if (i == 0) std::cout << (*it)->path[i].second << ")";
                    else std::cout << (*it)->path[i].second << "->";
                }
                maxTime=std::max(maxTime, (*it)->duration);
                minTime=std::min(minTime, (*it)->duration);
            }
            std::cout << "\n--------------"
                      << "\nYou'll have to wait " << maxTime - minTime << " minutes\n"
                      << "to meet each other in your destination"
                      << "\n--------------";
            count = temp;
            flag = false;
        }
        int increase;
        while (1) {
            std::cout << "\n\nIncrease group size (0 to quit): ";
            std::cin >> increase;
            if (increase < 0) std::cout << "Invalid size\n";
            else break;
        }
        if (increase == 0) break;
        size += increase;
        if (size <= count)
            std::cout << "\nThis route can still fit your group in";
        else if(size > maxCount) {
            std::cout << "\n--------------\n"
                      << "Your group is too large to handle\n(lose some friends, popstar)"
                      << "\n--------------\n";
            return;
        }
        else flag = true;
    }
    std::cout << "\n--------------";
}


void case_2_3() {
    int dataSet;
    while (1) {
        std::cout << "Choose Data Set [0-10]: ";
        std::cin >> dataSet;
        if (dataSet < 0 || dataSet > 10) std::cout << "Invalid Data Set\n";
        else break;
    }
    string fpath = get_fpath_2(dataSet);
    FulkersonGraph graph = FulkersonGraph(DATA_SET_2);
    int src, dest;
    std::cout << "### Case 2.3 ###\n";
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
    std::vector<std::pair<int, std::vector<int>>> paths;
    //graph.ford_fulkerson(src, dest, INT32_MAX, paths);
    std::cout << "\n## Paths ##";
    int count = 0;
    for (auto p: paths) {
        count += p.first;
    }
    std::cout << "\nTotal capacity: " << count;
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

#endif //DA_PROJECT_CASE2_H
