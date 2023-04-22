#include "graph.h"

namespace graph {

Graph::Graph() : adjacencyMatrix_{}, size_{0} {}

Graph::Graph(Matrix<unsigned int> data) : adjacencyMatrix_(data) {
    size_ = adjacencyMatrix_.getRows();
}

void Graph::LoadGraphFromFile(std::string filename) {
    std::ifstream infile(filename);

    if (infile.is_open()) {
        infile >> size_;
        Matrix<unsigned int> tmp(size_, size_);

        for (auto i = 0; i < size_; i++) {
            for (auto j = 0; j < size_; j++) {
                infile >> tmp(i, j);
            }
        }

        infile.close();
        adjacencyMatrix_ = tmp;
        std::cout << std::endl;
    } else {
        throw std::runtime_error("The file does not exist.");
    }
}

void Graph::PrintGraph() {
    for (int i = 0; i < adjacencyMatrix_.getRows(); i++) {
        std::cout << i + 1 << "--";
        for (int j = 0; j < adjacencyMatrix_.getRows(); j++) {
            if (adjacencyMatrix_(i, j) != 0) {
                std::cout << j + 1 << "--";
            }
        }
        std::cout << std::endl;
    }
}

void Graph::ExportGraphToDot(std::string filename) {
    std::ofstream outfile(filename);
    if (outfile.is_open()) {
        char letter = 'a';
        outfile << "graph graphname {\n";

        for (std::size_t i = 0; i < size_; i++) {
            outfile << '\t' << (char)(letter + i) << ";\n";
        }

        std::string edge = " -- ";
        for (std::size_t i = 0; i < size_; i++) {
            for (std::size_t j = 0; j < size_; j++) {
                if (adjacencyMatrix_(i, j) != adjacencyMatrix_(j, i)) {
                    edge = " -> ";
                    break;
                }
            }
        }

        for (std::size_t i = 0; i < size_; i++) {
            size_t j = (edge == " -- ") ? i : 0;
            for (; j < size_; j++) {
                if (adjacencyMatrix_(i, j) != 0) {
                    outfile << '\t' << (char)(letter + i) << edge
                            << (char)(letter + j) << ";\n";
                }
            }
        }

        outfile << '}';
        outfile.close();
    }
}

}  // namespace s21
