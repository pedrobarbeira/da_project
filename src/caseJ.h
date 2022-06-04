//
// Created by jljoa on 04/06/2022.
//

#ifndef DA_PROJECT_CASEJ_H
#define DA_PROJECT_CASEJ_H

#include "utils.h"
#include "testfulkerson.h"
#include<string.h>

void case_2_1(){

    GraphJ graph = GraphJ("tests/test03");

    int src, dest, size;
    std::cout << "### Case 2 ###\n";
//    while (1) {
//        std::cout << "Source: ";
//        std::cin >> src;
//        if (src <= 0 || src > graph.size()) std::cout << "Invalid source\n";
//        else break;
//    }
//    while (1) {
//        std::cout << "Dest: ";
//        std::cin >> dest;
//        if (dest <= 0 || dest > graph.size() || dest == src) std::cout << "Invalid dest\n";
//        else break;
//    }

    src = 1;
    dest = graph.size();


///    2.1 Determinar um encaminhamento para um grupo, dada a sua dimensão
/// 2.1 ---------------------------------------------------------

    std::cout << "2.1 Determinar um encaminhamento para um grupo, dada a sua dimensão\n";
    std::cout << "2.2 Corrigir um encaminhamento, se necessário, para que a dimensão do grupo possa aumentar de um número de unidades dado\n";
    std::cout << "2.3. Determinar a dimensão máxima do grupo e um encaminhamento\n";
    std::cout << "2.4. Partindo de um encaminhamento que constitui um grafo acíclico, determinar quando é que o grupo se reuniria novamente no destino, no mínimo\n";

    std::cout << "\n" << "STARTING ... (2.1)" << "\n";

    int groupSize;
    std::cout << "Group size : ";
    std::cin >> groupSize;
    if(graph.fordFulkerson_2_1(src,dest,groupSize)) {
        std::cout << "Final Path(s) (2.1): \n";
        graph.printPathListPairs();
    } else{
        graph.fordFulkerson(src, dest);
        std::cout << "Max Group Size : " << graph.getFluxValue(dest) << "\n";
        std::cout << "\n";
//        graph.printPathListPairs();
        return;
    }

    string option;
    while(1) {
        std::cout << "\n" << "Continue to (2.2) ? (yes/no)\n";
        std::cin >> option;
        if(option.compare("yes") == 0 || option.compare("no") == 0)
            break;
        std::cout << "Expected : yes/no\n";
    }
    if(option.compare("no") == 0)
        return;

/// 2.1 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

/// 2.2 Corrigir um encaminhamento, se necessário, para que a dimensão do grupo possa aumentar de um número de unidades dado
/// 2.2 ---------------------------------------------------------

    std::cout << "2.2 Corrigir um encaminhamento, se necessário, para que a dimensão do grupo possa aumentar de um número de unidades dado\n";
    std::cout << "2.3. Determinar a dimensão máxima do grupo e um encaminhamento\n";
    std::cout << "2.4. Partindo de um encaminhamento que constitui um grafo acíclico, determinar quando é que o grupo se reuniria novamente no destino, no mínimo\n";

    std::cout << "\n" << "STARTING ... (2.2)" << "\n";

    int groupSizeInc;
    std::cout << "Group size increment : ";
    std::cin >> groupSizeInc;
    std::cout << "Group size will be " << groupSize + groupSizeInc << "\n";
    if(graph.fordFulkerson_2_1(src,dest,groupSize + groupSizeInc)) {
        std::cout << "Final Path(s) (2.2): \n";
        graph.printPathListPairs();
    }   else{
        graph.fordFulkerson(src, dest);
        std::cout << "Max Group Size : " << graph.getFluxValue(dest) << "\n";
        return;
    }

//    string option;
    while(1) {
        std::cout << "\n" << "Continue to (2.3) ? (yes/no)\n";
        std::cin >> option;
        if(option.compare("yes") == 0 || option.compare("no") == 0)
            break;
        std::cout << "Expected : yes/no\n";
    }
    if(option.compare("no") == 0)
        return;

/// 2.2 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

/// 2.3. Determinar a dimensão máxima do grupo e um encaminhamento
/// 2.3 ---------------------------------------------------------

    std::cout << "2.3. Determinar a dimensão máxima do grupo e um encaminhamento\n";
    std::cout << "2.4. Partindo de um encaminhamento que constitui um grafo acíclico, determinar quando é que o grupo se reuniria novamente no destino, no mínimo\n";

    std::cout << "\n" << "STARTING ... (2.3)" << "\n";
    graph.fordFulkerson(src, dest);
    std::cout << "Max Group Size : " << graph.getFluxValue(dest) << "\n";
    std::cout << "Final Path(s) (2.3): \n";
    graph.printPathListPairs();


    while(1) {
        std::cout << "\n" << "Continue to (2.4) ? (yes/no)\n";
        std::cin >> option;
        if(option.compare("yes") == 0 || option.compare("no") == 0)
            break;
        std::cout << "Expected : yes/no\n";
    }
    if(option.compare("no") == 0)
        return;

/// 2.3 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

/// 2.4. Partindo de um encaminhamento que constitui um grafo acíclico,
/// determinar quando é que o grupo se reuniria novamente no destino, no mínimo
/// 2.4 ---------------------------------------------------------

    std::cout << "\n" << "STARTING ... (2.4)" << "\n";

    graph.groupTimeReunite_2_4(src,dest);

}

#endif //DA_PROJECT_CASEJ_H
