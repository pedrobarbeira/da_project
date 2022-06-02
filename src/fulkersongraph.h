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
    struct Edge {
        int dest;   // Destination node
        int capacity; // An integer weight
        bool active;
    };
    struct Node {
        int dist;
        int cap;
        int parent;
        list<Edge>adj;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    std::vector<Node> nodes; // The list of nodes being represented
public:


    explicit FulkersonGraph(int size) : n(size) {
        for (int i = 0; i <= size; i++) {
            add_node(i);
        }
    }

    explicit FulkersonGraph(std::string path) {
        std::ifstream infile(path);
        if (!infile.is_open()) throw FileNotFound(path);
        int noNodes, noEdges;
        infile >> noNodes >> noEdges;
        n = noNodes;
        *this = FulkersonGraph(noNodes);
        int src, dest, cap, dur;
        while (infile >> src) {
            infile >> dest >> cap >> dur;
            add_edge(src, dest, cap);
        }
    }

    void add_node(int val) {
        if (nodes.size() == n + 1) return;
        Node node;
        node.dist=0;
        node.adj.clear();
        nodes.push_back(node);
    }

    void add_edge(int src, int dest, int capacity = 1) {
        if (src < 1 || src > n || dest < 1 || dest > n) return;
        nodes[src].adj.push_back(Edge{dest, capacity, true});
    }

    int size() const{
        return n;
    }

    void max_capacity_min_dist(int src){
        for(int i=1;i<=n;i++){
            nodes[i].parent = 0;
            nodes[i].cap = 0;
            nodes[i].dist = INT32_MAX;
        }
        nodes[src].cap = INT32_MAX;
        nodes[src].dist=0;
        MaxHeap<int, int> maxHeap(n, -1);
        for(int i = 1; i <= n; i++)
            maxHeap.insert(i, nodes[i].cap);
        while(!maxHeap.empty()){
            int v = maxHeap.removeMax(); //gets node with larger capacity
            for(auto e : nodes[v].adj) {
                if (e.active) {
                    int w = e.dest;
                    if (std::min(nodes[v].cap, e.capacity) > nodes[w].cap) {
                        nodes[w].parent = v;
                        nodes[w].cap = std::min(nodes[v].cap, e.capacity);
                        nodes[w].dist = nodes[v].dist + 1;
                        maxHeap.increaseKey(w, nodes[w].cap);
                    } else if (std::min(nodes[v].cap, e.capacity) == nodes[w].cap
                               && nodes[v].dist + 1 < nodes[w].dist) {
                        nodes[w].parent=v;
                        nodes[w].dist = nodes[v].dist + 1;
                        maxHeap.increaseKey(w, nodes[w].cap);
                    }
                }
            }
        }
    }

    std::pair<int, vector<int>> retrieve_path(int src, int dest){
        std::pair<int, std::vector<int>> ret;
        if(nodes[dest].dist == INT32_MAX) return ret;
        ret.first = nodes[dest].cap;
        while(src!=dest){
            ret.second.push_back(dest);
            int v = nodes[dest].parent;
            for(auto e : nodes[v].adj)
                if(e.dest == dest) e.active=false;
            dest=v;
        }
        ret.second.push_back(src);
        return ret;
    }

};

#endif //DA_PROJECT_GRAPH_FORD_FULKERSON_H
