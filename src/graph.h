#ifndef PROJECT2_GRAPH_H
#define PROJECT2_GRAPH_H

#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include "exception.h"
#include "maxHeap.h"
#include <queue>
#include "minHeap.h"

class Graph {
    struct EdgeWeight{
        int capacity;
        int duration;
    };
    struct Edge {
        int dest;   // Destination node
        EdgeWeight weight; // An integer weight
    };

    struct Node {
        int parent;
        int parents;
        bool visited;
        int cap, dist;
        std::list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    std::vector<Node> nodes; // The list of nodes being represented

public:

    Graph(int size) : n(size){
        for(int i=0;i<=size;i++)
            add_node(i);
    }

    Graph(std::string path){
        std::ifstream infile(path);
        if(!infile.is_open()) throw FileNotFound(path);
        int noNodes, noEdges;
        infile>>noNodes>>noEdges;
        n=noNodes;
        *this = Graph(noNodes);
        int src, dest, cap, dur;
        while(infile>>src){
            infile>>dest>>cap>>dur;
            add_edge(src,dest, cap, dur);
        }
    }

    void add_node(int val){
        if(nodes.size() == n+1) return;
        Node node;
        node.visited = false;
        node.adj.clear();
        nodes.push_back(node);
    }

    void add_edge(int src, int dest, int capacity =1, int duration=1) {
        if (src < 1 || src >= n || dest < 1 || dest > n) return;
        nodes[src].adj.push_back(Edge{dest, EdgeWeight{capacity, duration}});
        if (!hasDir) nodes[dest].adj.push_back(Edge{dest, EdgeWeight{capacity, duration}});
    }

    int max_node_capacity(int n){
        return nodes[n].cap;
    }

    int size(){
        return n;
    }

    void max_capacity(int src){
        for(int i=1;i<=n;i++){
            nodes[i].parent = 0;
            nodes[i].cap = 0;
        }
        nodes[src].cap = INT32_MAX;
        MaxHeap<int, int> maxHeap(n, -1);
        for(int i = 1; i <= n; i++)
            maxHeap.insert(i, nodes[i].cap);
        while(!maxHeap.empty()){
            int v = maxHeap.removeMax(); //gets node with larger capacity
            for(auto e : nodes[v].adj){
                int w = e.dest;
                if(std::min(nodes[v].cap, e.weight.capacity) > nodes[w].cap){
                    nodes[w].cap = std::min(nodes[v].cap, e.weight.capacity);
                    nodes[w].parent=v;
                    maxHeap.increaseKey(w, nodes[w].cap);
                }
            }
        }
    }

    std::vector<int>path(int src, int dest){
        std::vector<int> ret;
        if(nodes[dest].cap == 0)
            return ret;
        while(dest != src){
            ret.push_back(dest);
            dest=nodes[dest].parent;
        }
        ret.push_back(src);
        return ret;
    }
};

#endif //PROJECT2_GRAPH_H
