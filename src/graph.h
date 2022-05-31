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
        int flow;
        EdgeWeight weight; // An integer weight
    };

    struct Node {
        int parent;
        bool visited;
        int cap, dist;
        std::list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        std::list<Edge> residual;
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
        nodes[src].adj.push_back(Edge{dest, 0, EdgeWeight{capacity, duration}});
        nodes[dest].residual.push_back(Edge{src, 0, EdgeWeight{0, duration}});
        if (!hasDir) nodes[dest].adj.push_back(Edge{dest, 0, EdgeWeight{capacity, duration}});
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
            std::cout << "-residual: \n";
            for(auto e : nodes[i].residual){
                std::cout << "\tdest: " << e.dest
                          << "\n\t\tcapacity: " << e.weight.capacity
                          << "\n\t\tduration: " << e.weight.duration
                          << std::endl;
            }
        }
        std::cout << "\nNodes: " << n
                  << "\nEdges: " << edgeCount
                  << std::endl;
    }

    int max_node_capacity(int n){
        return nodes[n].cap;
    }

    int size(){
        return n;
    }

    void max_flow(int src){
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
                    nodes[w].parent = v;
                    maxHeap.increaseKey(w, nodes[w].cap);
                }
            }
        }
    }

    void max_flow_min_dist(int src){
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
            for(auto e : nodes[v].adj){
                int w = e.dest;
                if(std::min(nodes[v].cap, e.weight.capacity) > nodes[w].cap){
                    nodes[w].cap = std::min(nodes[v].cap, e.weight.capacity);
                    nodes[w].parent = v;
                    nodes[w].dist=nodes[v].dist+1;
                    maxHeap.increaseKey(w, nodes[w].cap);
                }
                else if(std::min(nodes[v].cap, e.weight.capacity) == nodes[w].cap
                        && nodes[v].dist+1 < nodes[w].dist) {
                    nodes[w].parent = v;
                    nodes[w].dist = nodes[v].dist + 1;
                    maxHeap.increaseKey(w, nodes[w].cap);
                }
            }
        }
    }

    void min_dist_max_flow(int src){
        MinHeap<int, int> q(n, -1);
        for(int i=1;i<=n;i++){
            nodes[i].dist=INT32_MAX;
            nodes[i].cap=0;
            nodes[i].parent=0;
            nodes[i].visited=false;
            q.insert(i, nodes[i].dist);
        }
        nodes[src].dist=0;
        nodes[src].parent=src;
        nodes[src].cap=INT32_MAX;
        q.insert(src, nodes[src].dist);
        while(!q.empty()){
            int v=q.removeMin();
            if(!nodes[v].visited){
                nodes[v].visited=true;
                for(auto e : nodes[v].adj){
                    int w = e.dest;
                    if(!nodes[w].visited && nodes[v].dist+1 < nodes[w].dist){
                        nodes[w].dist=nodes[v].dist+1;
                        nodes[w].parent=v;
                        nodes[w].cap = std::min(nodes[v].cap, e.weight.capacity);
                        q.decreaseKey(w, nodes[w].dist);
                    }
                    else if(!nodes[w].visited && nodes[v].dist+1 == nodes[w].dist
                            && std::min(nodes[v].cap, e.weight.capacity) > nodes[w].cap){
                        nodes[w].dist=nodes[v].dist+1;
                        nodes[w].parent=v;
                        nodes[w].cap = std::min(nodes[v].cap, e.weight.capacity);
                        q.decreaseKey(w, nodes[w].dist);
                    }
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
        while(dest != src){
            ret.push_back(dest);
            dest=nodes[dest].parent;
        }
        ret.push_back(src);
        return ret;
    }

    int extract_max_cap(std::vector<int> path){
        int cap = INT32_MAX;
        for(unsigned int i=path.size()-1;i>0;i--){
            for(auto e : nodes[i].adj){
                if(e.dest==path[i-1])
                    cap=std::min(cap, e.weight.capacity);
            }
        }
        return cap;
    }

    void printflow(){
        for(int i=1;i<=n;i++){
            std::cout << i << "\nNormal:\n";
            for(auto e : nodes[i].adj){
                std::cout << "\tdest: " << e.dest << " flow: " << e.flow << std::endl;
            }
            std::cout << "\nResidual:\n";
            for(auto e : nodes[i].residual){
                std::cout << "\tdest: " << e.dest << " flow: " << e.flow << std::endl;
            }
        }
    }
};

#endif //PROJECT2_GRAPH_H
