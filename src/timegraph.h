//
// Created by pbarbeira on 04-06-2022.
//

#ifndef DA_PROJECT_TIMEGRAPH_H
#define DA_PROJECT_TIMEGRAPH_H

#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <queue>
#include "exception.h"

class TimeGraph{
    struct Edge{
        int dest;
        int weight;
    };
    struct Node{
        bool visited;
        int maxTime;
        int minTime;
        std::list<Edge*> adj;
    };
    int n;
    std::vector<Node> nodes;
public:
    explicit TimeGraph(int size) : n(size) {
        for (int i = 0; i <= size; i++) {
            add_node(i);
        }
    }

    void add_node(int val) {
        if (nodes.size() == n + 1) return;
        Node node;
        node.adj.clear();
        nodes.push_back(node);
    }

    void add_edge(int src, int dest, int weight) {
        if (src < 1 || src > n || dest < 1 || dest > n) return;
        bool flag = true;
        for(auto e : nodes[src].adj) {
            if (e->dest == dest) {
                flag = false;
                break;
            }
        }
        if(flag) nodes[src].adj.push_back(new Edge{dest, weight});
    }

    int size() const{
        return n;
    }

    void longest_time(int src){
        for(int i=1;i<=n;i++){
            nodes[i].maxTime=0;
            nodes[i].minTime=INT32_MAX;
        }
        std::queue<int> q;
        nodes[src].minTime=0;
        q.push(src);
        while(!q.empty()){
            int v = q.front();
            q.pop();
            for(auto e : nodes[v].adj) {
                int w = e->dest;
                nodes[w].maxTime = std::max(nodes[w].maxTime, nodes[v].maxTime + e->weight);
                nodes[w].minTime = std::min(nodes[w].minTime, nodes[v].minTime + e->weight);
                q.push(w);
            }
        }
    }

    std::vector<std::pair<int, int>> get_times(int src) {
        std::vector<std::pair<int, int>> times;
        std::queue<int> q;
        q.push(src);
        for (auto n: nodes)
            n.visited = false;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            if(!nodes[v].visited) {
                nodes[v].visited = true;
                if (nodes[v].maxTime != 0 && nodes[v].minTime != INT32_MAX)
                    times.push_back({v, nodes[v].maxTime - nodes[v].minTime});
                for (auto e: nodes[v].adj) {
                    int w = e->dest;
                    q.push(e->dest);
                }
            }
        }
        return times;
    }

    int final_time(int dest){
        return nodes[dest].maxTime - nodes[dest].minTime;
    }

};

#endif //DA_PROJECT_TIMEGRAPH_H
