//
// Created by pbarbeira on 24-05-2022.
//

#ifndef PROJECT2_GRAPH_H
#define PROJECT2_GRAPH_H

#include <iostream>
#include <list>
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
        bool visited;
        int cap, dist;
        std::list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    std::vector<Node> nodes; // The list of nodes being represented

public:

    Graph(int size, bool dir=false) : n(size), hasDir(dir){
        Node node;
        nodes.push_back(node);
    }

    void addNode(int val){
        if(nodes.size() == n+1) return;
        Node node;
        node.parent = 0;
        node.visited = false;
        node.adj.clear();
        nodes.push_back(node);
    }

    void addEdge(int src, int dest, int capacity =1, int duration=1) {
        if (src < 1 || src >= n || dest < 1 || dest > n) return;
        nodes[src].adj.push_back(Edge{dest, EdgeWeight{capacity, duration}});
        if (!hasDir) nodes[dest].adj.push_back(Edge{dest, EdgeWeight{capacity, duration}});
    }

    void print(){
        int edgeCount = 0;
        for(int i=1;i<=n;i++){
            std::cout << "src: " << i << ":\n";
            for(auto e : nodes[i].adj){
                std::cout << "\tdest: " << e.dest
                          << "\n\t\tcapacity: " << e.weight.capacity
                          << "\n\t\tduration: " << e.weight.duration
                          << std::endl;
                edgeCount++;
            }
        }
        std::cout << "\nNodes: " << n
                  << "\nEdges: " << edgeCount
                  << std::endl;
    }

    void max_flow(int src){
        for(auto node : nodes){
            node.parent = NULL;
            node.cap = 0;
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
                    nodes[w].parent = v;
                    maxHeap.increaseKey(w, nodes[w].cap);
                }
            }
        }
    }

    std::vector<int>path(int src, int dest){
        std::vector<int> ret;
        if(nodes[dest].cap == 0){
            std::cout << "No path from " << src << " to " << dest << '\n';
            return ret;
        }
        while(src != dest){
            ret.push_back(dest);
            dest=nodes[dest].parent;
        }
        ret.push_back(src);
        return ret;
    }

    void dijkstra(int src){
        MinHeap<int, int> q(n, -1);
        for(int i=1;i<=n;i++){
            nodes[i].dist=INT32_MAX;
            nodes[i].visited=false;
            q.insert(i, nodes[i].dist);
        }
        nodes[src].dist=0;
        nodes[src].parent=src;
        q.insert(src, nodes[src].dist);
        while(!q.empty()){
            int v=q.removeMin();
            if(!nodes[v].visited){
                nodes[v].visited=true;
                for(auto e : nodes[v].adj){
                    int w;
                    if(!nodes[w].visited && nodes[v].dist+1 < nodes[w].dist){
                        nodes[w].dist=nodes[v].dist+1;
                        nodes[w].parent=v;
                    }
                }
            }
        }
    }
};

#endif //PROJECT2_GRAPH_H
