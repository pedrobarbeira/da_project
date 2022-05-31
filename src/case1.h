#ifndef DA_PROJECT_CASE1_H
#define DA_PROJECT_CASE1_H

#include <vector>
#include <fstream>
#include <sstream>
#include "graph.h"
#include "exception.h"
#include "utils.h"


void case_1_1(Graph& graph) {
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
    graph.max_flow(src);
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

void case_1_2(Graph& graph) {
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
    graph.max_flow_min_dist(src);
    std::vector<int> path = graph.path(src, dest);
    std::stringstream s;
    s << '(';
    for (int i = path.size() - 1; i >= 0; i--) {
        if (i == 0) s << path[i] << ')';
        else s << path[i] << ", ";
    }
    std::cout << "Maximum capacity: " << graph.max_node_capacity(dest)
              << "\nPath: " << s.str() << std::endl;
    s.str("");
    s.clear();
    graph.min_dist_max_flow(src);
    path=graph.path(src, dest);
    int cap = graph.extract_max_cap(path);
    s << '(';
    for (int i = path.size() - 1; i >= 0; i--) {
        if (i == 0) s << path[i] << ')';
        else s << path[i] << ", ";
    }
    std::cout << "Shortest path: " << s.str()
              << "\nCapacity: " << cap << std::endl;

}


#endif //DA_PROJECT_CASE1_H
