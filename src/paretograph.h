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

class ParetoGraph {
    struct EdgeWeight {
        int capacity;
        int duration;
    };
    struct Edge {
        int dest;   // Destination node
        EdgeWeight weight; // An integer weight
    };

    struct Node {
        int dist, cpt;
        std::vector<std::vector<int>> parents;
        std::vector<int> cap;
        std::list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    std::vector<Node> nodes; // The list of nodes being represented

public:

    ParetoGraph(int size) : n(size) {
        hasDir=true;
        for (int i = 0; i <= size; i++)
            add_node(i);
    }

    ParetoGraph(std::string path) {
        std::ifstream infile(path);
        if (!infile.is_open()) throw FileNotFound(path);
        int noNodes, noEdges;
        infile >> noNodes >> noEdges;
        n = noNodes;
        *this = ParetoGraph(noNodes);
        int src, dest, cap, dur;
        while (infile >> src) {
            infile >> dest >> cap >> dur;
            add_edge(src, dest, cap, dur);
        }
    }

    void add_node(int val) {
        if (nodes.size() == n + 1) return;
        Node node;
        node.parents.clear();
        node.adj.clear();
        nodes.push_back(node);
    }

    void add_edge(int src, int dest, int capacity = 1, int duration = 1) {
        if (src < 1 || src >= n || dest < 1 || dest > n) return;
        nodes[src].adj.push_back(Edge{dest, EdgeWeight{capacity, duration}});
        if (!hasDir) nodes[dest].adj.push_back(Edge{dest, EdgeWeight{capacity, duration}});
    }

    int size(){
        return n;
    }

    void max_capacity_min_distance(int src){
        for(int i=1;i<=n;i++){
            nodes[i].dist = 0;
            nodes[i].cpt = 0;
        }
        nodes[src].cpt = INT32_MAX;
        nodes[src].dist=0;
        MaxHeap<int, int> maxHeap(n, -1);
        for(int i = 1; i <= n; i++)
            maxHeap.insert(i, nodes[i].cpt);
        while(!maxHeap.empty()){
            int v = maxHeap.removeMax(); //gets node with larger capacity
            for(auto e : nodes[v].adj){
                int w = e.dest;
                if(std::min(nodes[v].cpt, e.weight.capacity) > nodes[w].cpt){
                    nodes[w].cpt = std::min(nodes[v].cpt, e.weight.capacity);
                    nodes[w].dist=nodes[v].dist+1;
                    maxHeap.increaseKey(w, nodes[w].cpt);
                }
                else if(std::min(nodes[v].cpt, e.weight.capacity) == nodes[w].cpt
                        && nodes[v].dist+1 < nodes[w].dist){
                    nodes[w].dist=nodes[v].dist+1;
                }
            }
        }
    }

    int max_distance(int src){
        int max = 0;
        for(int i=1;i<=n;i++)
            nodes[i].dist = 0;
        std::queue<int> q;
        q.push(src);
        while(!q.empty()){
            int v = q.front(); //gets node with larger capacity
            q.pop();
            for(auto e : nodes[v].adj){
                int w = e.dest;
                if(nodes[v].dist+1> nodes[w].dist){
                    nodes[w].dist = nodes[v].dist+1;
                    max = std::max(nodes[w].dist, max);
                    q.push(w);
                }
            }
        }
        return max;
    }

    void pareto_optimal(int src, int dest){
        max_capacity_min_distance(src);
        int min_dist=nodes[dest].dist;
        for(int i=1;i<=n;i++){
            nodes[i].parents.clear();
            for(int j=0;j<=min_dist;j++) {
                std::vector<int> vec;
                nodes[i].parents.push_back(vec);
                nodes[i].cap.push_back(0);
                nodes[i].dist=INT32_MAX;
            }
        }
        std::queue<int> q;
        nodes[src].dist=0;
        q.push(src);
        int v, w, i;
        while(!q.empty()){
            v=q.front();
            q.pop();
            for(auto e:nodes[v].adj){
                w=e.dest;
                i=nodes[v].dist+1;
                if(i<=nodes[dest].dist && nodes[w].cap[i] < e.weight.capacity){
                    nodes[w].cap[i]=e.weight.capacity;
                    nodes[w].parents[i].clear();
                    nodes[w].parents[i].push_back(v);
                    nodes[w].dist=i;
                }
                q.push(w);
            }
        }
    }

    void path_builder(int src, int dest, int dist, std::vector<int>& path, std::vector<std::vector<int>>& ret){
        if(dist==0)
            ret.push_back(path);
        std::vector<int>root=path;
        for(auto i : nodes[dest].parents[dist]){
            root.push_back(i);
            path_builder(src, i, dist-1, root, ret);
        }
    }

    std::vector<std::vector<int>>optimal_paths(int src, int dest){
        std::vector<std::vector<int>> ret;
        if(nodes[dest].parents.empty()) return ret;
        std::vector<int> path;
        path.push_back(dest);
        for(int i=0;i<nodes[dest].parents.size();i++){
            if(!nodes[dest].parents[i].empty()){
                path_builder(src, dest, i, path, ret);
            }
        }
        return ret;
    }
};


#endif //DA_PROJECT_PARETOGRAPH_H
