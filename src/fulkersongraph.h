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
        int flow;
        int capacity; // An integer weight
        bool active;
    };
    struct Node {
        int dist;
        int cap;
        int parent;
        list<Edge*>adj;
        list<Edge*> residual;
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
        nodes[src].adj.push_back(new Edge{dest, 0, capacity, true});
        nodes[dest].residual.push_back(new Edge{src, 0, capacity, true});
    }

    int size() const{
        return n;
    }

    void gamma_bfs(int src){
        for(int i=1;i<=n;i++){
            nodes[i].parent = 0;
            nodes[i].cap=0;
        }
        std::queue<int> q;
        nodes[src].cap=INT32_MAX;
        q.push(src);
        int v, w;
        while(!q.empty()){
            v = q.front();
            q.pop();
            for(auto e : nodes[v].residual){
                if(e->active) {
                    w = e->dest;
                    nodes[v].parent = w;
                    q.push(w);
                }
            }
        }
    }

    void calculate_residual(){
        int v, w;
        for(int i=1;i<=n;i++){
            for(auto e : nodes[i].residual){
                if(e->active) {
                    v = e->dest;
                }
                for(auto j : nodes[v].adj){
                    w = j->dest;
                    if(v == w) e->flow=j->capacity - j->flow;
                }
            }

        }
    }

    bool path_exists(int src, int dest, std::vector<Edge*>& g){
        while(dest != src){
            if (nodes[dest].parent == 0)
                return false;
            else{
                for(auto e : nodes[dest].residual)
                    if(e->dest == nodes[dest].parent)
                        g.push_back(e);
                dest = nodes[dest].parent;
            }
        }
        return true;
    }

    void ford_fulkerson(int src, int dest, std::vector<std::pair<int, std::vector<int>>>& paths){
        for(auto n : nodes){
            for(auto e : n.adj){
                e->flow=1;
            }
            for(auto e : n.residual){
                e->flow=1;
            }
        }
        std::vector<Edge*> g;
        std::pair<int, std::vector<int>> path;
        calculate_residual();
        gamma_bfs(dest);
        while(path_exists(src, dest, g)){
            int c = INT32_MAX, cap = INT32_MAX;
            bool flag = false;
            path.second.push_back(dest);
            for(auto e : g) {
                path.second.push_back(e->dest);
                c = std::min(c, e->flow);
                cap = std::min(cap, e->capacity);
            }
            int t = dest;
            while(t!=src){
                for(auto e : g){
                    for(auto i : nodes[e->dest].adj){
                        if(i->dest == t){
                            i->flow += c;
                            if(i->flow < e->capacity)
                                e->flow = e->capacity - i->flow;
                            else {
                                e->flow = 0;
                                e->active = false;
                                flag = true;
                            }
                            t=e->dest;
                        }
                    }
                }
            }
            if(flag){
                path.first = cap;
                paths.push_back(path);
                flag = false;
            }
            path.second.clear();
            calculate_residual();
            gamma_bfs(dest);
            g.clear();
        }
    }

};

#endif //DA_PROJECT_GRAPH_FORD_FULKERSON_H
