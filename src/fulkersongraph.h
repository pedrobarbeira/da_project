//
// Created by pbarbeira on 01-06-2022.
//

#ifndef DA_PROJECT_GRAPH_FORD_FULKERSON_H
#define DA_PROJECT_GRAPH_FORD_FULKERSON_H

#include <iostream>
#include <list>
#include <stack>
#include <fstream>
#include "exception.h"
#include "maxHeap.h"
#include <queue>
#include "minHeap.h"

class FulkersonGraph {
    struct EdgeWeight {
        int capacity;
        int duration;
    };
    struct Edge {
        int dest;   // Destination node
        EdgeWeight weight; // An integer weight
    };
    struct ResidualEdge {
        int src;
        int flow;
    };

    struct Node {
        int dist;
        std::vector<std::vector<int>> parents;
        std::list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        std::list<ResidualEdge> res;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    std::vector<Node> nodes; // The list of nodes being represented
public:

}

#endif //DA_PROJECT_GRAPH_FORD_FULKERSON_H
