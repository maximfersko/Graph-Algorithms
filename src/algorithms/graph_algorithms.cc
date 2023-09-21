#include "graph_algorithms.h"

namespace algorithms {

std::vector<unsigned int> GraphAlgoritms::BreadthFirstSearch(graph_t &graph,
                                                             int startVertex) {
    size_t size_matrix = graph.GetSize();
    if (startVertex > size_matrix || startVertex < 1)
        throw std::invalid_argument("Start vertex out of range !");
    queue<unsigned int> vertices;
    Matrix<unsigned int> gMatrix = graph.GetAdjacencyMatrix();
    std::vector<bool> visited(size_matrix, false);
    std::vector<unsigned int> result;
    vertices.push(startVertex - 1);
    visited[startVertex - 1] = true;
    while (!vertices.empty()) {
        unsigned int currentVertex = vertices.front();
        vertices.pop();
        for (unsigned int i = 0; i < size_matrix; ++i) {
            if (gMatrix(currentVertex, i) && !visited[i]) {
                vertices.push(i);
                visited[i] = true;
            }
        }
        result.push_back(++currentVertex);
    }
    return result;
}

std::vector<unsigned int> GraphAlgoritms::DepthFirstSearch(graph_t &graph,
                                                           int startVertex) {
    size_t size_matrix = graph.GetSize();
    if (startVertex > size_matrix || startVertex < 1) {
        throw std::invalid_argument("Start vertex out of range !");
    }
    stack<unsigned int> vertices;
    Matrix<unsigned int> gMatrix = graph.GetAdjacencyMatrix();
    std::vector<bool> visited(size_matrix, false);
    std::vector<unsigned int> result;
    vertices.push(startVertex - 1);
    visited[startVertex - 1] = true;
    while (!vertices.empty()) {
        unsigned int currentVertex = vertices.top();
        vertices.pop();
        for (unsigned int i = size_matrix - 1; i > 0; --i) {
            unsigned int index = i - 1;
            if (gMatrix(currentVertex, index) && !visited[index]) {
                vertices.push(index);
                visited[index] = true;
            }
        }

        result.push_back(++currentVertex);
    }
    return result;
}

double GraphAlgoritms::GetShortestPathBetweenVertices(graph_t &graph, int vertex1,
                                                      int vertex2) {
    size_t size_matrix = graph.GetSize();
    if (vertex1 > size_matrix || vertex2 > size_matrix || vertex1 < 1 ||
        vertex2 < 1)
        throw std::invalid_argument("Vertex out of range !");
    const auto inf = std::numeric_limits<double>::infinity();
    std::vector<double> distance(size_matrix, inf);
    std::vector<bool> visited(size_matrix, false);
    distance[vertex1 - 1] = 0;
    for (int i = 0; i < size_matrix - 1; i++) {
        int u = -1;
        for (int j = 0; j < size_matrix; j++) {
            if (!visited[j] && (u == -1 || distance[j] < distance[u])) {
                u = j;
            }
        }
        if (u < 0) return 0.;
        visited[u] = true;
        for (int vertex = 0; vertex < size_matrix; ++vertex) {
            double weight = graph.GetAdjacencyMatrix()(u, vertex);
            if (weight != 0 && distance[u] + weight < distance[vertex]) {
                distance[vertex] = distance[u] + weight;
            }
        }
    }
    return distance[vertex2 - 1];
}

Matrix<unsigned int> GraphAlgoritms::GetShortestPathsBetweenAllVertices(
    graph_t &graph) {
    Matrix<unsigned int> graph_matrix = graph.GetAdjacencyMatrix();
    size_t size_matrix = graph.GetSize();
    for (size_t i = 0; i < size_matrix; ++i) {
        for (size_t j = 0; j < size_matrix; ++j) {
            if (graph_matrix(i, j) == 0 && i != j) {
                graph_matrix(i, j) =
                    std::numeric_limits<unsigned int>::infinity();
            }
        }
    }

    for (size_t i = 0; i < size_matrix; ++i) {
        for (size_t j = 0; j < size_matrix; ++j) {
            for (size_t k = 0; k < size_matrix; ++k) {
                graph_matrix(j, k) =
                    std::min(graph_matrix(j, k),
                             (graph_matrix(j, i) + graph_matrix(i, k)));
            }
        }
    }

    return graph_matrix;
}

}  // namespace s21
