#include "menu.h"

namespace interface {

void Menu::PrintMenu() {
    std::cout << std::endl
              << "|========================  Menu  =========================|"
              << std::endl
              << "|                                                         |"
              << std::endl
              << "|                     Choose action:                      |"
              << std::endl
              << "|                                                         |"
              << std::endl
              << "|                1. Load graph from file                  |"
              << std::endl
              << "|                2. Traversal in breadth                  |"
              << std::endl
              << "|                 3. Traversal in depth                   |"
              << std::endl
              << "|          4. Shortest path between two vertices          |"
              << std::endl
              << "|         5. Shortest paths between all vertices          |"
              << std::endl
              << "|             6.Search Minimal spanning tree              |"
              << std::endl
              << "|                 7. Salesman problem                     |"
              << std::endl
              << "|                                                         |"
              << std::endl
              << "|                       0. Exit                           |"
              << std::endl
              << "|=========================================================|"
              << std::endl
              << std::endl
              << "-> ";
}

void Menu::run() {
    do {
        std::cin.get(action_);
        if (action_ == '\n') {
            system("clear");
            PrintMenu();
        } else {
            SelectAction();
            if (next_) {
                std::cout << std::endl << "Press Enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                '\n');
            }
        }
    } while (action_ != '0');
}

void Menu::LoadGraph() {
    std::string pathFileName;
    std::cout << "Enter file path:" << std::endl << "-> ";
    std::cin >> pathFileName;
    try {
        graph_.LoadGraphFromFile(pathFileName);
        graph_.PrintGraph();
        std::cout << "The graph is successfully loaded!" << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
}

std::pair<int, int> Menu::GetVertex(bool isOneVertex) {
    if (isOneVertex) {
        int startVertex = 0;
        std::cout << "Enter start vertex: " << std::endl << "-> ";
        std::cin >> startVertex;
        return std::make_pair(startVertex, 0);
    } else {
        int startVertex = 0, endVertex = 0;
        std::cout << "Enter start vertex and end vertex: " << std::endl
                  << "-> ";
        std::cin >> startVertex;
        std::cin >> endVertex;
        return std::make_pair(startVertex, endVertex);
    }
}

void Menu::BreadthSearch() {
    try {
        PrintVertex(
            Algorihms::BreadthFirstSearch(graph_, GetVertex(true).first));
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}

void Menu::DepthSearch() {
    try {
        PrintVertex(
            Algorihms::DepthFirstSearch(graph_, GetVertex(true).first));
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}

void Menu::ShortestPathBetweenTwoVertices() {
    try {
        std::pair<int, int> vertices = GetVertex(false);
        std::cout << "Result: " << std::endl
                  << Algorihms::GetShortestPathBetweenVertices(
                         graph_, vertices.first, vertices.second);
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}

void Menu::ShortestPathBetweenAllVertices() {
    std::cout << "Result: " << std::endl;
    Algorihms::GetShortestPathsBetweenAllVertices(graph_).print();
}

void Menu::FindMinimalSpainingTree() {
    std::cout << "Result: " << std::endl;
    Algorihms::GetLeastSpanningTree(graph_).PrintGraph();
}

void Menu::SolveTravelingSalesmanProblems() {
    try {
        tsm_t result =
            Algorihms::SolveTravelingSalesmanProblem(graph_);
        std::cout << "Result: " << std::endl;
        for (auto item : result.vertices_) std::cout << item << " ";
        std::cout << std::endl << "Distance: " << result.distance_;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
}

void Menu::PrintVertex(std::vector<unsigned int> vertices) {
    std::cout << "Result: " << std::endl;
    for (auto elm : vertices) std::cout << elm << " ";
}

void Menu::SelectAction() {
    system("clear");
    switch (action_) {
        case '1':
            LoadGraph();
            break;
        case '2':
            BreadthSearch();
            break;
        case '3':
            DepthSearch();
            break;
        case '4':
            ShortestPathBetweenTwoVertices();
            break;
        case '5':
            ShortestPathBetweenAllVertices();
            break;
        case '6':
            FindMinimalSpainingTree();
            break;
        case '7':
            SolveTravelingSalesmanProblems();
            break;
        case '0':
            system("clear");
            exit(0);
        default:
            std::cout << "Select an item from 0 to 7" << std::endl;
            break;
    }
}

}  // namespace s21
