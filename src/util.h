//
// Created by jljoa on 22/05/2022.
//
#ifndef PROJECT2_UTIL_H
#define PROJECT2_UTIL_H

#include <iostream>
#include <cmath>
#include <exception.h>
#include <fstream>
#include "graph.h"

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


#endif //PROJECT2_UTIL_H
