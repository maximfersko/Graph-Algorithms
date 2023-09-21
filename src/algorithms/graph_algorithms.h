#pragma once

#include <iostream>
#include <limits>

#include "../containers/queue.hpp"
#include "../containers/stack.hpp"
#include "../graph/graph.h"
namespace algorithms {

template <class T>
using queue = containers::Queue<T>;
template <class K>
using stack = containers::Stack<K>;
using graph_t = graph::Graph;
using tsm_t = graph::TsmResult;

class GraphAlgoritms {
   public:
    GraphAlgoritms() {}
    ~GraphAlgoritms() = default;

    static std::vector<unsigned int> DepthFirstSearch(graph_t &graph,
                                                      int startVertex);
    static std::vector<unsigned int> BreadthFirstSearch(graph_t &graph,
                                                        int startVertex);
    static double GetShortestPathBetweenVertices(graph_t &graph, int vertex1,
                                                 int vertex2);
    static Matrix<unsigned int> GetShortestPathsBetweenAllVertices(
        graph_t &graph);

   private:
    graph_t graph_;
};

}  // namespace Algorithms