#ifndef PROJECT2_UTIL_H
#define PROJECT2_UTIL_H

#include <cmath>
#include <exception.h>
#include <fstream>
#include "graph.h"

static string TEST_SET_1 = "tests/in01.txt";
static string DATA_SET_1 = "tests/in01.txt";
static string DATA_SET_2 = "tests/in01.txt";
static string DATA_SET_3 = "tests/in01.txt";
static string DATA_SET_4 = "tests/in01.txt";
static string DATA_SET_5 = "tests/in01.txt";
static string DATA_SET_6 = "tests/in01.txt";
static string DATA_SET_7 = "tests/in01.txt";
static string DATA_SET_8 = "tests/in01.txt";
static string DATA_SET_9 = "tests/in01.txt";
static string DATA_SET_10 = "tests/in01.txt";

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
        graph.add_node(i);
    int src, dest, capacity, duration;
    while(noEdges > 0){
        infile >> src;
        infile >> dest;
        infile >> capacity;
        infile >> duration;
        graph.add_edge(src, dest, capacity, duration);
        noEdges--;
    }
    return graph;
}


#endif //PROJECT2_UTIL_H
