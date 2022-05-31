#include <iostream>
#include "case1.h"

int main() {
    Graph graph(0);
    try {
        graph = readFile(TEST_SET_1);
    }
    catch (FileNotFound &e) {
        std::cout << e.what();
        return 1;
    }
    graph.printflow();
    return 0;
}
