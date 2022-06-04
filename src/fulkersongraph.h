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

struct Path{
    std::vector<std::pair<int, int>> path;
    int capacity;
    int duration = 0;
};

class FulkersonGraph {
    struct Weight{
        int capacity;
        int duration;
    };
    struct Edge {
        int dest;   // Destination node
        int flow;
        Weight* weight; // An integer weight
        bool active;
    };
    struct Node {
        int cap;
        bool visited;
        int parent;
        Edge* parentEdge;
        list<Edge*>adj;
    };
    std::vector<Path*> paths;
    int n;              // Graph size (vertices are numbered from 1 to n)
    std::vector<Node> nodes; // The list of nodes being represented
public:


    explicit FulkersonGraph(int size) : n(size) {
        for (int i = 0; i <= size; i++) {
            add_node(i);
        }
        paths.clear();
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
            add_edge(src, dest, cap, dur);
        }
    }

    void add_node(int val) {
        if (nodes.size() == n + 1) return;
        Node node;
        node.adj.clear();
        nodes.push_back(node);
    }

    void add_edge(int src, int dest, int capacity, int duration) {
        if (src < 1 || src > n || dest < 1 || dest > n) return;
        nodes[src].adj.push_back(new Edge{dest, 0, new Weight{capacity, duration}, true});
    }

    int size() const{
        return n;
    }

    bool augmenting_path(int src, int dest, std::vector<Edge*> &v){
        for(int i=1;i<=n;i++){
            nodes[i].cap=0;
            nodes[i].visited=false;
            nodes[i].parentEdge=nullptr;
        }
        std::queue<int> q;
        nodes[src].cap=INT32_MAX;
        q.push(src);
        while(!q.empty()) {
            int v = q.front();
            nodes[v].visited = true;
            q.pop();
            for (auto e: nodes[v].adj) {
                if (e->active) {
                    int w = e->dest;
                    if (!nodes[w].visited) {
                        int c = std::min(nodes[v].cap, e->weight->capacity);
                        if (nodes[w].cap < c) {
                            nodes[w].cap = c;
                            nodes[w].parentEdge = e;
                            nodes[w].parent = v;
                        }
                        q.push(w);
                    }
                }
            }
        }
        if(nodes[dest].parentEdge==nullptr) return false;
        while(dest != src){
            v.push_back(nodes[dest].parentEdge);
            dest = nodes[dest].parent;
        }
        return true;
    }

    void ford_fulkerson(int src, int dest){
        for(int i=1;i<=n;i++){
            nodes[i].cap=0;
            for(auto e:nodes[i].adj){
                e->flow=0;
            }
        }
        std::vector<Edge*> g;
        while(augmenting_path(src, dest, g)){
            int c = INT32_MAX;
            for(auto v : g)
                c = std::min(c, v->weight->capacity);
            Path* p = new Path;
            for(auto e : g){
                if(e->flow + c > e->weight->capacity)
                    c -= e->flow + c - e->weight->capacity;
            }
            p->capacity = c;
            for(auto e : g){
                e->flow += c;
                if(e->flow == e->weight->capacity)
                    e->active = false;
                p->path.push_back({e->weight->duration, e->dest});
                p->duration += e->weight->duration;
            }
            p->path.push_back({0, 1});
            paths.push_back(p);
            g.clear();
        }
    }

    std::vector<Path*> get_paths() const{
        return paths;
    }
};

#endif //DA_PROJECT_GRAPH_FORD_FULKERSON_H
