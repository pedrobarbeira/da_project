#ifndef DA_PROJECT_CASE1_H
#define DA_PROJECT_CASE1_H

#include <vector>
#include <fstream>
#include <sstream>
#include "graph.h"
#include "exception.h"

Graph readFile(std::string path){
    std::ifstream infile(path);
    if(!infile.is_open()){
        std::cout << "Error reading file " << path << '\n';
        throw FileNotFound(path);
    }
    int noNodes, noEdges;
    infile >> noNodes;
    infile >> noEdges;
    Graph graph(noNodes, true);
    for(int i = 0; i < noNodes; i++)
        graph.addNode(i);
    int src, dest, capacity, duration;
    while(noEdges > 0){
        infile >> src;
        infile >> dest;
        infile >> capacity;
        infile >> duration;
        graph.addNode(src);
        graph.addNode(dest);
        graph.addEdge(src, dest, capacity, duration);
        noEdges--;
    }
    return graph;
}

void case_1_1(std::string dataset) {
    Graph graph(0);
    try {
        graph = readFile(dataset);
    }
    catch (FileNotFound &e) {
        std::cout << e.what();
        return;
    }
    int src, dest;
    std::cout << "### Case 1 ###\n";
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

void case_1_2(std::string dataset) {
    Graph graph(0);
    try {
        graph = readFile(dataset);
    }
    catch (FileNotFound &e) {
        std::cout << e.what();
        return;
    }
    int src, dest;
    std::cout << "### Case 1 ###\n";
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
    s.str("");
    s.clear();
    graph.dijkstra(src);
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
