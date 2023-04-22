#pragma once

#include <string>
#include <iostream>
#include <unistd.h>
#include "../algorithms/graph_algorithms.h"
#include "../graph/graph.h"

namespace interface {

using Algorihms = algorithms::GraphAlgoritms;
using graph_t = graph::Graph;
using tsm_t = graph::TsmResult; 

class Menu {
public:

    Menu() : action_('\0'), next_(true) {}
    ~Menu() {}
    void run();

private:
    graph_t graph_;
    char action_;
    bool next_;
   
    void PrintMenu();
    void LoadGraph();
    void SelectAction();
    void BreadthSearch();
    void DepthSearch();
    void ShortestPathBetweenTwoVertices();
    void ShortestPathBetweenAllVertices();
    void FindMinimalSpainingTree();
    void SolveTravelingSalesmanProblems();
    std::pair<int, int> GetVertex(bool isOneVertex);
    void PrintVertex(std::vector<unsigned int> verticess);
};

};