//
// Created by pbarbeira on 03-06-2022.
//

#ifndef DA_PROJECT_TESTFULKERSON_H
#define DA_PROJECT_TESTFULKERSON_H



#include <iostream>
#include <list>
#include "maxHeap.h"
#include <queue>
//#include <rpcdce.h>
#include "minHeap.h"

class GraphJ {
    struct EdgeWeight{
        int capacity;
        int duration;
    };
    struct Edge {
        int orig;
        int dest;   // Destination node
        int flow;
//        bool visited;
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

    list<pair<list<int>,int>> pathsList = {};
public:

    GraphJ(int size, bool dir=false) : n(size), hasDir(dir){
        Node node;
        nodes.push_back(node);
    }

    explicit GraphJ(std::string path) {
        std::ifstream infile(path);
        if (!infile.is_open()) throw FileNotFound(path);
        int noNodes, noEdges;
        infile >> noNodes >> noEdges;
        n = noNodes;
        *this = GraphJ(noNodes);
        int src, dest, cap, dur;
        while (infile >> src) {
            infile >> dest >> cap >> dur;
            addEdge(src, dest, cap, dur);
        }
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
        Edge toaddEdge = Edge{src, dest, 0, EdgeWeight{capacity, duration}};
        nodes[src].adj.push_back(Edge{src, dest, 0, EdgeWeight{capacity, duration}});
        nodes[dest].residual.push_back(Edge{dest, src, 0, EdgeWeight{0, duration}});
        if (!hasDir) nodes[dest].adj.push_back(Edge{dest, dest, 0, EdgeWeight{capacity, duration}});
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

    void fordFulkerson(int source, int dest){

        this->resetFlows();

//        std::cout << "Result : " << this->findAugmentationPath(source, dest) << "\n";
        while(this->findAugmentationPath(source, dest)){
//            std::cout << "Another improvement..\n";
            int f = findMinResidualAlongPath(source, dest);
            augmentFlowAlongPath(source, dest, f);
            updateEdges();
//            printFlows();
        }

//        std::cout << "ENded\n";
    }

    bool fordFulkerson_2_1(int source, int dest, int groupSize){

        this->resetFlows();

//        std::cout << "Result : " << this->findAugmentationPath(source, dest) << "\n";
        while(this->findAugmentationPath(source, dest)){
//            std::cout << "Another improvement..\n";
            int f = findMinResidualAlongPath(source, dest);
            augmentFlowAlongPath(source, dest, f);
            updateEdges();
//            printFlows();
            if(getFluxValue(dest) >= groupSize)
                break;
        }
        if(getFluxValue(dest) < groupSize) {
            std::cout << "\nGroup is too big\n";
            return false;
        }

//        std::cout << "FF ended\n";
        return true;
    }

    void augmentFlowAlongPath(int s, int t, int flow) {

        int curV = t;

//        std::cout << "augmentFlowAlo.. flow - "<< flow << " \n";
        while(curV != s){
            if(nodes[curV].parentEdge.dest == curV){
//                std::cout << "flow of "<< nodes[curV].parentEdge.orig << "-" << curV << " is " << nodes[curV].parentEdge.flow <<  "/ " << nodes[curV].parentEdge.weight.capacity <<"\n";
                nodes[curV].parentEdge.flow += flow;
//                std::cout << "flow of "<< nodes[curV].parentEdge.orig << "-" << curV << " is " << nodes[curV].parentEdge.flow << "\n";
//                std::cout << "flow added : " << flow << "\n";
                curV = nodes[curV].parent;
            }
            else{
                nodes[curV].parentEdge.flow -= flow;
                curV = nodes[curV].parentEdge.dest;
            }
        }


    }

    double findMinResidualAlongPath(int s, int t) { //Starts from the end and goes to the beginning in order to find the maxFlow

        int f = INT32_MAX;
        int curV = t;
        list<int> pathList = {};

        std::cout << "finding min residual path : " << curV;
        pathList.push_back(curV);
        while(curV != s) {
//            Edge e = nodes[curV].parentEdge;
//            std::cout << "curV(" << curV << ") - s(" << s << ")\n";
            if(nodes[curV].parentEdge.dest == curV){
                f = std::min(f, nodes[curV].parentEdge.weight.capacity - nodes[curV].parentEdge.flow);
                curV = nodes[curV].parent;
                std::cout << " " << curV << " ";
                pathList.push_back(curV);
            }
            else{
                f = std::min(f, nodes[curV].parentEdge.flow);
                curV = nodes[curV].parentEdge.dest;
                std::cout << " " << curV << " ";
                pathList.push_back(curV);
            }
        }
        pair<list<int>,int> pathPair;
        pathList.reverse();
        pathPair.first = pathList;
        pathPair.second = f;
        pathsList.push_back(pathPair);
//        list<pair<list<int>,int>> path = {};
        std::cout << " \n";
        return f;

    }

    bool findAugmentationPath(int s, int t) { //Edmonds-Karp

        for(int i = 0; i < nodes.size(); i++){
            nodes[i].visited = false;
        }

        nodes[s].visited = true;
        std::queue<int> q;
        q.push(s);

        while(!q.empty() && !nodes[t].visited){
            int curV = q.front();

            q.pop();
            for(auto e: nodes[curV].adj){
                this->testAndVisit(q, curV, e, e.dest,e.weight.capacity - e.flow);
            }

            /// Visit
//            for(auto e: nodes[curV].residual){
//                this->testAndVisit(q, curV, e, e.dest, e.flow);
//            }
        }

        return nodes[t].visited;

    }

    void testAndVisit(std::queue< int> &q,int parentNode , Edge e, int toVisitNode, double residual) { //Tests the edge and visits the node

        if(!nodes[toVisitNode].visited && residual > 0){
//            std::cout << "Visiting.. " << toVisitNode << "\n";
            nodes[toVisitNode].visited = true;
            nodes[toVisitNode].parent = parentNode;
            nodes[toVisitNode].parentEdge = e;
            q.push(toVisitNode);
        }

    }

    void resetFlows(){
        for(auto v : nodes){
            for(auto e : v.adj){
                e.flow = 0;
            }
            for(auto e : v.residual){
                e.flow = 0;
            }
        }
    }

    void printFlows(){
        std::stringstream ss;

        for(int i = 1; i < nodes.size(); i++){
//            std::cout << "Cycle\n";
            ss << i << "-> (";
            for (auto e : nodes[i].adj)
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

    void updateEdges(){
        for(int i = 1; i < nodes.size(); i++){
            for(Edge &e : nodes[i].adj){
                for(int p = 1; p < nodes.size(); p++){
                    if(nodes[p].parentEdge.dest == e.dest && nodes[p].parentEdge.orig == e.orig ){
                        e.flow = nodes[p].parentEdge.flow;
                    }
                }
            }
        }
    }

    int getFluxValue(int dest){
        int totalFlux = 0;
        for(Node n : nodes){
            for(Edge e : n.adj){
                if(e.dest == dest){
                    totalFlux += e.flow;
                }
            }
        }
//        std::cout << "Max Group Size : " << totalFlux << "\n";
        return totalFlux;
    }
    //From dest to src using parent node...
    void printPathPN(int src, int dest){
//        int printArr[nodes.size()];
        list<int> printList = {};
        int curV = dest;
        while(curV != src){
            printList.push_back(curV);
            curV = nodes[curV].parent;
        }
        printList.push_back(curV);
        printList.reverse();

        for(int node : printList)
            std::cout << " " << node;

        std::cout << "\n";
    }

    //From src to dest by edges with flow > 0
    void printPathFF(int src, int dest){
//        std::array<string> strArray = {}
        int startNode = src;
        Edge prevEdge;
        for(Edge e : nodes[src].adj){
            if(e.flow > 0){
                std::cout << src << " " << e.dest;
                int destNode = e.dest;
                prevEdge = e;
                //Se os grupos se cruzarem a meio do caminho haverá problema?
                //Uma vez que à primeira aresta adj que tem flow ele muda de nó
                //Solução? Criar visited para Edges para saber se ja visitou essa edge? X
                while(destNode != dest){
                    for(Edge e1 : nodes[destNode].adj){
                        if(e1.flow > 0 ){
//                            e1.visited = true;
                            std::cout << " " << e1.dest;
                            destNode = e1.dest;
                            prevEdge = e1;
                            break;
                        }
                    }

                }
            }
            std::cout << "\n";
        }
    }

    //From src to dest by edges with flow > 0
    list<list<int>> getPathFF(int src, int dest){
        list<list<int>> printList = {};
        int startNode = src;
        for(Edge e : nodes[src].adj){
            if(e.flow > 0){
                list<int> templist = {};
                templist.push_back(src);
//                std::cout << src << " " << e.dest;
                int destNode = e.dest;
                //Se os grupos se cruzarem a meio do caminho haverá problema?
                //Uma vez que à primeira aresta adj que tem flow ele muda de nó
                //Solução? Criar visited para Edges para saber se ja visitou essa edge? X
                while(destNode != dest){
                    for(Edge e1 : nodes[destNode].adj){
                        if(e1.flow > 0){
//                            std::cout << " " << e1.dest;
                            templist.push_back(destNode);
                            destNode = e1.dest;
                            break;
                        }
                    }

                }
                printList.push_back(templist);
            }
//            std::cout << "\n";
        }
        return printList;
    }

    void groupTimeReunite_2_4(int src, int dest){
//        list<pair<list<int>,int>> path = {};
//        list<list<int>> paths = getPathFF(src, dest);
        int maxTime = 0;
        for (pair<list<int>,int> list : pathsList){
            int sumTime = 0;
            int prevNode = -1;
            std::cout << "PATH -> ";
            for (int node : list.first) {
                std::cout << " " << node;
                if (prevNode != -1) {
                    for (Edge e : nodes[prevNode].adj) {
                        if (e.dest == node) {
                            sumTime += e.weight.duration;
                        }
                    }
                    prevNode = node;
                } else {
                    prevNode = node;
                }
            }
            if (sumTime > maxTime)
                maxTime = sumTime;
            std::cout << "\n" << "Duration : " << sumTime;
            std::cout << "\n\n";

        }

        std::cout << "Group reunites after : " << maxTime << " (units?)" << "\n";
    }

    void printPathListPairs(){
//                list<pair<list<int>,int>> path = {};
        for(pair<list<int>,int> pairAux: pathsList){
            for(int node : pairAux.first){
                std::cout << " " << node;
            }
            std::cout << " | Flow - " << pairAux.second << "\n";
        }
    }


};

#endif //DA_PROJECT_TESTFULKERSON_H
