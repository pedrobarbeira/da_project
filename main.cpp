#include <iostream>
#include "util.h"
#include "graph.h"

int main() {
    std::string FILEPATH = "tests/in01.txt";
    try {
        Graph graph = readFile(FILEPATH);
        graph.max_flow(1);
        std::cout << "No dijskstra:\n";
        std::vector<int> path = graph.path(1, 4);
        for(int i = path.size()-1; i >=0; i--)
            std::cout << path[i] << ' ';
        std::cout << "\nLine changes: " << path.size()-1 << std::endl;

        std::cout << "Now dijkstra:\n";
        graph.dijkstra(1);


        path = graph.path(1, 4);
        for(int i = path.size()-1; i >=0; i--)
            std::cout << path[i] << ' ';
        std::cout << "\nLine changes: " << path.size()-1 << std::endl;

    }
    catch(FileNotFound& e){
        e.what();
    }
    return 0;
}
