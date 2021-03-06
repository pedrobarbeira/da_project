//
// Created by pbarbeira on 01-06-2022.
//

#ifndef DA_PROJECT_PARETOGRAPH_H
#define DA_PROJECT_PARETOGRAPH_H

#include <iostream>
#include <list>
#include <stack>
#include <fstream>
#include "exception.h"
#include "maxHeap.h"
#include <queue>
#include "minHeap.h"

enum colors{WHITE, GRAY, BLACK};

class ParetoGraph {
    struct Edge {
        int dest;   // Destination node
        int capacity; // An integer weight
    };

    struct Node {
        int dist, cpt;
        std::vector<std::vector<int>> parents;
        std::vector<int> cap;
        std::list<Edge*> adj; // The list of outgoing edges (to adjacent nodes)
    };
    int n;              // Graph size (vertices are numbered from 1 to n)
    int min_cap;
    std::vector<Node*> nodes; // The list of nodes being represented

public:

    explicit ParetoGraph(int size) : n(size) {
        for (int i = 0; i <= size; i++) {
            add_node(i);
        }
    }

    explicit ParetoGraph(std::string path) {
        std::ifstream infile(path);
        if (!infile.is_open()) throw FileNotFound(path);
        int noNodes, noEdges;
        infile >> noNodes >> noEdges;
        n = noNodes;
        *this = ParetoGraph(noNodes);
        int src, dest, cap, dur;
        while (infile >> src) {
            infile >> dest >> cap >> dur;
            add_edge(src, dest, cap);
        }
    }

    void add_node(int val) {
        if (nodes.size() == n + 1) return;
        Node* node = new Node;
        node->dist=0;
        node->cpt=0;
        node->parents.clear();
        node->adj.clear();
        nodes.push_back(node);
    }

    void add_edge(int src, int dest, int capacity = 1) {
        if (src < 1 || src > n || dest < 1 || dest > n) return;
        nodes[src]->adj.push_back(new Edge{dest, capacity});
    }

    int size() const{
        return n;
    }

    void max_capacity_min_dist(int src) {
        for (int i = 1; i <= n; i++) {
            nodes[i]->cpt = 0;
            nodes[i]->dist = INT32_MAX;
        }
        nodes[src]->cpt = INT32_MAX;
        nodes[src]->dist = 0;
        MaxHeap<int, int> maxHeap(n, -1);
        for (int i = 1; i <= n; i++)
            maxHeap.insert(i, nodes[i]->cpt);
        while (!maxHeap.empty()) {
            int v = maxHeap.removeMax(); //gets node with larger capacity
            for (auto e: nodes[v]->adj) {
                int w = e->dest;
                if (std::min(nodes[v]->cpt, e->capacity) > nodes[w]->cpt) {
                    nodes[w]->cpt = std::min(nodes[v]->cpt, e->capacity);
                    nodes[w]->dist = nodes[v]->dist + 1;
                    maxHeap.increaseKey(w, nodes[w]->cpt);
                } else if (std::min(nodes[v]->cpt, e->capacity) == nodes[w]->cpt
                           && nodes[v]->dist + 1 < nodes[w]->dist) {
                    nodes[w]->dist = nodes[v]->dist + 1;
                    maxHeap.increaseKey(w, nodes[w]->cpt);
                }
            }
        }
    }

    void min_dist_max_capacity(int src, int dest){
        for(int i=1;i<=n;i++){
            nodes[i]->dist = INT32_MAX;
            nodes[i]->cpt = 0;
        }
        nodes[src]->dist=0;
        nodes[src]->cpt = INT32_MAX;
        std::queue<int> q;
        q.push(src);
        while(!q.empty()){
            int v = q.front();
            q.pop();
            for(auto e : nodes[v]->adj) {
                int w = e->dest;
                if (nodes[v]->dist + 1 < nodes[w]->dist) {
                    nodes[w]->dist = nodes[v]->dist + 1;
                    nodes[w]->cpt = std::min(nodes[v]->cpt, e->capacity);
                    q.push(w);
                } else if (nodes[v]->dist + 1 == nodes[w]->dist
                           && std::min(nodes[v]->cpt, e->capacity) > nodes[w]->cpt) {
                    nodes[w]->cpt = std::min(nodes[v]->cpt, e->capacity);
                    q.push(w);
                }
            }
        }
        min_cap = nodes[dest]->cpt;
    }

    void pareto_optimal(int src, int dest){
        max_capacity_min_dist(src);
        if(nodes[dest]->dist==INT32_MAX) return;
        int max_dist=nodes[dest]->dist;
        int max_cap=nodes[dest]->cpt;
        min_dist_max_capacity(src, dest);
        for(int i=1;i<=n;i++){
            nodes[i]->parents.clear();
            nodes[i]->dist=0;
            nodes[i]->cpt=INT32_MAX;
            for(int j=0;j<=max_dist;j++) {
                std::vector<int> vec;
                nodes[i]->parents.push_back(vec);
                nodes[i]->cap.push_back(0);
                nodes[i]->dist=INT32_MAX;
            }
        }
        nodes[src]->dist=0;
        nodes[dest]->cap[max_dist] = max_cap;
        for(auto e : nodes[src]->adj)
            pareto_recursive(src, e, dest, max_dist);
    }

    void pareto_recursive(int v, Edge* edge, const int& dest, const int& max_dist) {
        int w = edge->dest;
        int i = nodes[v]->dist + 1;
        nodes[w]->dist = i;
        nodes[w]->cpt = std::min(nodes[v]->cpt, edge->capacity);
        if(nodes[w]->cpt < nodes[dest]->cap[i]){
            return;
        }
        if (nodes[w]->parents[i].empty()) {
            nodes[w]->parents[i].push_back(v);
        } else if (nodes[w]->cap[i] <= nodes[w]->cpt) {
            if (nodes[w]->cap[i] < nodes[w]->cpt) {
                nodes[w]->cap[i] = nodes[w]->cpt;
                nodes[w]->parents[i].clear();
            }
            bool flag = true;
            for(auto  x : nodes[w]->parents[i]){
                if(x == v){
                    flag = false;
                    break;
                }
            }
            if(flag) nodes[w]->parents[i].push_back(v);
        }
        if (w == dest || i == max_dist) {
            return;
        }
        for (auto e: nodes[w]->adj)
            if(e->capacity >= min_cap)
                pareto_recursive(w, e, dest, max_dist);
    }

    void path_builder(int src, int dest, int dist, std::pair<int, std::vector<int>>& path, std::vector<std::pair<int, std::vector<int>>>& ret){
        if(dist==0)
            ret.push_back(path);
        std::pair<int, std::vector<int>>root=path;
        for(auto i : nodes[dest]->parents[dist]){
            root.second.push_back(i);
            path_builder(src, i, dist-1, root, ret);
            root=path;
        }
    }

    std::vector<std::pair<int, std::vector<int>>>optimal_paths(int src, int dest){
        std::vector<std::pair<int, std::vector<int>>> ret;
        if(nodes[dest]->parents.empty()) return ret;
        std::pair<int, std::vector<int>> path;
        path.second.push_back(dest);
        int prevCap = 0;
        for(int i=0;i<nodes[dest]->parents.size();i++){
            if(nodes[dest]->cap[i] > prevCap && !nodes[dest]->parents[i].empty()){
                path.first = nodes[dest]->cap[i];
                path_builder(src, dest, i, path, ret);
            }
            prevCap = nodes[dest]->cap[i];
        }
        return ret;
    }
};

#endif