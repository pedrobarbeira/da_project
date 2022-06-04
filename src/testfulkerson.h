//
// Created by pbarbeira on 03-06-2022.
//

#ifndef DA_PROJECT_TESTFULKERSON_H
#define DA_PROJECT_TESTFULKERSON_H


#include <iostream>
#include <fstream>
#include <list>
#include "maxHeap.h"
#include <queue>
#include <sstream>
#include "minHeap.h"
#include "exception.h"

class TestGraph {
    struct EdgeWeight {
        int capacity;
        int duration;
    };
    struct Edge {
        int orig;
        int dest;   // Destination node
        int flow;
        EdgeWeight weight; // An integer weight
    };

    struct Node {
        int parent;
        bool visited;
        int cap, dist;
        Edge parentEdge = Edge{0, 0, 0, EdgeWeight{0, 0}};
        std::list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        std::list<Edge> residual;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    std::vector<Node> nodes; // The list of nodes being represented

public:

    explicit TestGraph(int size) : n(size) {
        for (int i = 0; i <= size; i++) {
            add_node(i);
        }
    }

    explicit TestGraph(std::string path) {
        std::ifstream infile(path);
        if (!infile.is_open()) throw FileNotFound(path);
        int noNodes, noEdges;
        infile >> noNodes >> noEdges;
        n = noNodes;
        *this = TestGraph(noNodes);
        int src, dest, cap, dur;
        while (infile >> src) {
            infile >> dest >> cap >> dur;
            add_edge(src, dest, cap);
        }
    }

    int size(){
        return n;
    }

    void add_node(int val) {
        if (nodes.size() == n + 1) return;
        Node node;
        node.parent = 0;
        node.visited = false;
        node.adj.clear();
        nodes.push_back(node);
    }

    void add_edge(int src, int dest, int capacity = 1, int duration = 1) {
        if (src < 1 || src >= n || dest < 1 || dest > n) return;
        Edge toaddEdge = Edge{src, dest, 0, EdgeWeight{capacity, duration}};
        nodes[src].adj.push_back(Edge{src, dest, 0, EdgeWeight{capacity, duration}});
        nodes[dest].residual.push_back(Edge{dest, src, 0, EdgeWeight{0, duration}});
    }


    void ford_fulkerson(int source, int dest) {

        this->resetFlows();

//        std::cout << "Result : " << this->findAugmentationPath(source, dest) << "\n";
        while (this->findAugmentationPath(source, dest)) {
            std::cout << "Another improvement..\n";
            int f = findMinResidualAlongPath(source, dest);
            augmentFlowAlongPath(source, dest, f);
            updateEdges();
            //printFlows();
        }

        std::cout << "ENded\n";
    }

    void augmentFlowAlongPath(int s, int t, int flow) {

        int curV = t;

        std::cout << "augmentFlowAlo.. flow - " << flow << " \n";
        while (curV != s) {
            if (nodes[curV].parentEdge.dest == curV) {
//                std::cout << "flow of "<< nodes[curV].parentEdge.orig << "-" << curV << " is " << nodes[curV].parentEdge.flow <<  "/ " << nodes[curV].parentEdge.weight.capacity <<"\n";
                nodes[curV].parentEdge.flow += flow;
//                std::cout << "flow of "<< nodes[curV].parentEdge.orig << "-" << curV << " is " << nodes[curV].parentEdge.flow << "\n";
//                std::cout << "flow added : " << flow << "\n";
                curV = nodes[curV].parent;
            } else {
                nodes[curV].parentEdge.flow -= flow;
                curV = nodes[curV].parentEdge.dest;
            }
        }


    }

    double findMinResidualAlongPath(int s,
                                    int t) { //Starts from the end and goes to the beginning in order to find the maxFlow

        int f = INT32_MAX;
        int curV = t;
        std::cout << "PATH :" << curV;
        while (curV != s) {
//            Edge e = nodes[curV].parentEdge;
//            std::cout << "curV(" << curV << ") - s(" << s << ")\n";
            if (nodes[curV].parentEdge.dest == curV) {
                f = std::min(f, nodes[curV].parentEdge.weight.capacity - nodes[curV].parentEdge.flow);
                curV = nodes[curV].parent;
                std::cout << " " << curV << " ";
            } else {
                f = std::min(f, nodes[curV].parentEdge.flow);
                curV = nodes[curV].parentEdge.dest;
                std::cout << " " << curV << " ";
            }
        }
        std::cout << " \n";
        return f;

    }

    bool findAugmentationPath(int s, int t) { //Edmonds-Karp

        for (int i = 0; i < nodes.size(); i++) {
            nodes[i].visited = false;
        }

        nodes[s].visited = true;
        std::queue<int> q;
        q.push(s);

        while (!q.empty() && !nodes[t].visited) {
            int curV = q.front();

            q.pop();
            for (auto e: nodes[curV].adj) {
                this->testAndVisit(q, curV, e, e.dest, e.weight.capacity - e.flow);
            }

            /// Visit
//            for(auto e: nodes[curV].residual){
//                this->testAndVisit(q, curV, e, e.dest, e.flow);
//            }
        }

        return nodes[t].visited;

    }

    void testAndVisit(std::queue<int> &q, int parentNode, Edge e, int toVisitNode,
                      double residual) { //Tests the edge and visits the node

        if (!nodes[toVisitNode].visited && residual > 0) {
//            std::cout << "Visiting.. " << toVisitNode << "\n";
            nodes[toVisitNode].visited = true;
            nodes[toVisitNode].parent = parentNode;
            nodes[toVisitNode].parentEdge = e;
            q.push(toVisitNode);
        }

    }

    void resetFlows() {
        for (auto v: nodes) {
            for (auto e: v.adj) {
                e.flow = 0;
            }
            for (auto e: v.residual) {
                e.flow = 0;
            }
        }
    }

    void printFlows() {
        std::stringstream ss;

        for (int i = 1; i < nodes.size(); i++) {
//            std::cout << "Cycle\n";
            ss << i << "-> (";
            for (auto e: nodes[i].adj)
                ss << (e.dest) << "[Flow: " << e.flow << "] ";
            ss << ") || ";
        }

        std::cout << ss.str() << std::endl << std::endl;

//        std::cout << "Parent Edge Flow : \n";
//        std::stringstream ss2;
//
//        for(int i = 1; i < nodes.size(); i++){
////            std::cout << "Cycle\n";
//            ss2 << i << "-> (";
////            for (auto e : nodes[i].residual)
//                ss2 << (nodes[i].parentEdge.dest) << "[Flow: " << nodes[i].parentEdge.flow << "] ";
//            ss2 << ") || ";
//        }
//
//        std::cout << ss2.str() << std::endl << std::endl;

    }

    void updateEdges() {
        for (int i = 1; i < nodes.size(); i++) {
            for (Edge &e: nodes[i].adj) {
                for (int p = 1; p < nodes.size(); p++) {
                    if (nodes[p].parentEdge.dest == e.dest && nodes[p].parentEdge.orig == e.orig) {
                        e.flow = nodes[p].parentEdge.flow;
                    }
                }
            }
        }
    }

    void printFluxValue(int dest) {
        int totalFlux = 0;
        for (Node n: nodes) {
            for (Edge e: n.adj) {
                if (e.dest == dest) {
                    totalFlux += e.flow;
                }
            }
        }
        std::cout << "Max Group Size : " << totalFlux << "\n";
    }

    void printPathFF(int src, int dest) {
//        std::array<string> strArray = {}
        int startNode = src;
        for (Edge e: nodes[src].adj) {
            if (e.flow > 0) {
                std::cout << src << " " << e.dest;
                int destNode = e.dest;
                //Se os grupos se cruzarem a meio do caminho haverá problema?
                //Uma vez que à primeira aresta adj que tem flow ele muda de nó
                //Solução? Criar visited para Edges para saber se ja visitou essa edge? X
                while (destNode != dest) {
                    for (Edge e1: nodes[destNode].adj) {
                        if (e1.flow > 0) {
                            std::cout << " " << e1.dest;
                            destNode = e1.dest;
                            break;
                        }
                    }

                }
            }
            std::cout << "\n";
        }
    }
};


#endif //DA_PROJECT_TESTFULKERSON_H
