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
        int parent;
        Edge* parentEdge;
        list<Edge*> parents;
        list<Edge*>adj;
        list<Edge*> residual;
    };
    FulkersonGraph* paths;
    int n;              // Graph size (vertices are numbered from 1 to n)
    std::vector<Node> nodes; // The list of nodes being represented
public:


    explicit FulkersonGraph(int size) : n(size) {
        for (int i = 0; i <= size; i++) {
            add_node(i);
        }
        paths = nullptr;
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
        node.parent=0;
        node.adj.clear();
        nodes.push_back(node);
    }

    void add_edge(int src, int dest, int capacity, int duration) {
        if (src < 1 || src > n || dest < 1 || dest > n) return;
        nodes[src].adj.push_back(new Edge{dest, 0, new Weight{capacity, duration}, true});
        nodes[dest].residual.push_back(new Edge{src, 0, new Weight{capacity, duration}, true});
    }

    void add_edge(int src, int dest, Weight* w){
        if (src < 1 || src > n || dest < 1 || dest > n) return;
        nodes[src].adj.push_back(new Edge{dest, 0, w, true});
    }

    void add_edge(int src, Edge* e){
        nodes[e->dest].adj.push_back(new Edge{src, 0, e->weight, true});
    }

    int size() const{
        return n;
    }

    void reset_graph(){
        for(int i=1;i<=n;i++){
            nodes[i].parent =0;
            nodes[i].parentEdge=nullptr;
            nodes[i].cap=0;
            for(auto e: nodes[i].adj){
                e->flow=0;
                e->active=true;
            }
            for(auto e: nodes[i].residual){
                e->flow=0;
                e->active=true;
            }
        }
    }

    void residual_network(){
        for(int i=1;i<=n;i++){
            for(auto e : nodes[i].adj){
                for(auto j: nodes[e->dest].residual){
                    if(j->dest==i){
                        j->flow = e->weight->capacity - e->flow;
                        if(j->flow <= 0)
                            j->active = false;
                    }
                }
            }
        }
    }

    bool augmenting_path(int src, int dest){
        std::stack<int> q;
        nodes[dest].cap=INT32_MAX;
        q.push(dest);
        while(!q.empty()){
            int v = q.top();
            q.pop();
            for(auto e : nodes[v].residual) {
                if (e->active) {
                    int w = e->dest;
                    nodes[w].cap = std::min(nodes[v].cap, e->flow);
                    nodes[v].parentEdge = e;
                    if (w == src) return true;
                    q.push(w);
                }
            }
        }
        return false;
    }

    void ford_fulkerson(int src, int dest){
        if(paths == nullptr)
            paths = new FulkersonGraph(n);
        residual_network();
        std::vector<Edge*> g;
        while(augmenting_path(src, dest)){
            int v = dest;
            do{
                g.push_back(nodes[v].parentEdge);
                v = nodes[v].parentEdge->dest;
            }while(v != src);
            int c = INT32_MAX;
            for(auto e : g){
                c = std::min(c, e->flow);
            }
            v=dest;
            for(auto e : g){
                e->flow -= c;
                for(auto i : nodes[e->dest].adj){
                    if(i->dest == v) {
                        i->flow += c;
                        e->flow = i->weight->capacity - i->flow;
                        if(e->flow <= 0)
                            e->active = false;
                        break;
                    }
                }
                bool flag=false;
                for(auto j : nodes[v].parents){
                    if(j == e) flag = true;
                    break;
                }
                if(!flag) nodes[v].parents.push_back(e);
                v=e->dest;
            }
            g.clear();
        }
    }

    void path_builder(int src, int dest, Edge* e, std::pair<int, std::vector<int>> path, std::vector<std::pair<int, std::vector<int>>> &v) {
        std::pair<int, std::vector<int>> root = path;
        root.first = std::min(root.first, e->weight->capacity);
        dest = e->dest;
        root.second.push_back(dest);
        if (dest == src) v.push_back(root);
        else {
            for (auto j: nodes[e->dest].parents)
                path_builder(src, e->dest, j, root, v);
        }
    }

    std::vector<std::pair<int, std::vector<int>>> extract_paths(int src, int dest){
        std::vector<std::pair<int, std::vector<int>>> v;
        std::pair<int, std::vector<int>> path;
        path.second.push_back(dest);
        for(auto e : nodes[dest].parents){
            path.first = e->weight->capacity;
            path_builder(src, dest, e, path, v);
        }
        return v;
    }
};

#endif //DA_PROJECT_GRAPH_FORD_FULKERSON_H
