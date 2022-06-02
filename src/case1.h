#ifndef DA_PROJECT_CASE1_H
#define DA_PROJECT_CASE1_H

#include <vector>
#include <fstream>
#include <sstream>
#include "graph.h"
#include "paretograph.h"
#include "exception.h"
#include "utils.h"


void case_1_1(Graph& graph) {
    int src, dest;
    std::cout << "### Case 1.1 ###\n";
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
        else s << path[i] << ", ";
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
    ParetoGraph graph(0);
    switch(dataSet) {
        case 0: graph = ParetoGraph(TEST_SET_1); break;
        case 1: graph = ParetoGraph(DATA_SET_1); break;
        case 2: graph = ParetoGraph(DATA_SET_2); break;
        case 3: graph = ParetoGraph(DATA_SET_3); break;
        case 4: graph = ParetoGraph(DATA_SET_4); break;
        case 5: graph = ParetoGraph(DATA_SET_5); break;
        case 6: graph = ParetoGraph(DATA_SET_6); break;
        case 7: graph = ParetoGraph(DATA_SET_7); break;
        case 8: graph = ParetoGraph(DATA_SET_8); break;
        case 9: graph = ParetoGraph(DATA_SET_9); break;
        case 10: graph= ParetoGraph(DATA_SET_10); break;
        default: return;
    }

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
