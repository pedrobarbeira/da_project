#ifndef DA_PROJECT_CASE1_H
#define DA_PROJECT_CASE1_H

#include <vector>
#include <fstream>
#include <sstream>
#include "graph.h"
#include "paretograph.h"
#include "exception.h"
#include "utils.h"


void case_1_1() {
    std::cout << "### Case 1.1 ###\n";
    int dataSet;
    while (1) {
        std::cout << "Choose Data Set [0-10]: ";
        std::cin >> dataSet;
        if (dataSet < 0 || dataSet > 10) std::cout << "Invalid Data Set\n";
        else break;
    }
    string fpath = get_fpath_1(dataSet);
    Graph graph = Graph(fpath);
    int src, dest;
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
    graph.max_capacity(src);
    std::vector<int> path = graph.path(src, dest);
    std::stringstream s;
    s << '(';
    for (int i = path.size() - 1; i >= 0; i--) {
        if (i == 0) s << path[i] << ')';
        else s << path[i] << "->";
    }
    std::cout << "Maximum capacity: " << graph.max_node_capacity(dest)
              << "\nPath: " << s.str() << std::endl;
    s.clear();
}

void case_1_2() {
    int dataSet;
    while (1) {
        std::cout << "Choose Data Set [0-10]: ";
        std::cin >> dataSet;
        if (dataSet < 0 || dataSet > 10) std::cout << "Invalid Data Set\n";
        else break;
    }
    string fpath = get_fpath_1(dataSet);
    ParetoGraph graph = ParetoGraph(fpath);
    int src, dest;
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

    graph.pareto_optimal(src, dest);
    std::vector<std::pair<int, std::vector<int>>> paths = graph.optimal_paths(src, dest);
    std::cout << "\n## Paths ##";
    if(paths.empty()){
        std::cout << "\n--------------\n"
                  << "Unfortunately there are no paths\n(you'll have to walk)";
    }
    for(auto v : paths){
        std::cout << "\n--------------";
        std::cout << "\nNumber of transitions: " << v.second.size()-1
                  << "\nCapacity: " << v.first
                  << "\nPath: (";
        for(int i=v.second.size()-1;i>=0;i--){
            if(i==0) std::cout << v.second[i] << ")";
            else std::cout << v.second[i] << "->";
        }
    }
    std::cout << "\n--------------";

}


#endif //DA_PROJECT_CASE1_H
