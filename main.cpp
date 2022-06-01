#include <iostream>
#include "case1.h"
#include "graph_pareto.h"

int main() {
    ParetoGraph graph(0);
    try {
        graph = ParetoGraph(TEST_SET_1);
    }
    catch (FileNotFound &e) {
        std::cout << e.what();
        return 1;
    }
    case_1_2();
    return 0;
}
