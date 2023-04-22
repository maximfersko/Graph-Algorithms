#pragma once

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../containers/matrix.h"

namespace graph {

struct TsmResult {
    std::vector<std::size_t> vertices_;
    unsigned distance_;
};

class Graph {
   public:
    Graph();
    explicit Graph(Matrix<unsigned int> matrix);
    ~Graph() = default;

    void LoadGraphFromFile(std::string filename);
    void ExportGraphToDot(std::string filename);
    void PrintGraph();

    std::size_t GetSize() { return size_; }
    Matrix<unsigned int> GetAdjacencyMatrix() { return adjacencyMatrix_; }
    void SetSize(std::size_t size) { size_ = size; }
    void SetAdjacencyMatrix(const Matrix<unsigned int> *matrix) {
        adjacencyMatrix_ = *matrix;
    }

   private:
    Matrix<unsigned int> adjacencyMatrix_;
    std::size_t size_;
};

}  // namespace s21
