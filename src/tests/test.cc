#include <gtest/gtest.h>

#include "../algorithms/graph_algorithms.h"
#include "../graph/graph.h"

//    ########################
//    ##                    ##
//    ##    LOAD_GRAPH      ##
//    ##                    ##
//    ########################


TEST(load_graph, firstSuite) {
    algorithms::graph_t graph;
    graph.LoadGraphFromFile("./tests/data/examp3");
    Matrix<unsigned int> matrix({0,  9,  75, 0,  0,  9,  0, 95, 19,
                                 42, 75, 95, 0,  51, 66, 0, 19, 51,
                                 0,  31, 0,  42, 66, 31, 0});
    ASSERT_EQ(true, matrix == graph.GetAdjacencyMatrix());
}

TEST(load_graph, secondSuite) {
    algorithms::graph_t graph;
    graph.LoadGraphFromFile("./tests/data/examp5");
    Matrix<unsigned int> matrix(
        {0, 1, 1, 1, 0, 0, 1, 2, 1, 1, 0, 1, 1, 2, 1, 0});
    ASSERT_EQ(true, matrix == graph.GetAdjacencyMatrix());
}

//    ########################
//    ##                    ##
//    ##    BREADTH_SEARCH  ##
//    ##                    ##
//    ########################

TEST(graph_breadth_search, tree) {
    Matrix<unsigned int> data({0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0,
                               0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0});
    algorithms::graph_t graph(data);
    algorithms::GraphAlgoritms algoritms;
    auto result = algoritms.BreadthFirstSearch(graph, 1);
    std::size_t path[]{1, 2, 3, 4, 5};
    for (int i = 0; i < result.size(); ++i) EXPECT_EQ(result[i], path[i]);
}

TEST(graph_breadth_search, not_connected) {
    Matrix<unsigned int> data({0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0});
    algorithms::graph_t graph(data);
    algorithms::GraphAlgoritms algoritms;
    auto result = algoritms.BreadthFirstSearch(graph, 1);
    std::size_t path[]{1, 3};
    for (int i = 0; i < result.size(); ++i) EXPECT_EQ(result[i], path[i]);
}

TEST(graph_breadth_search, trees) {
    Matrix<unsigned int> data({0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0,
                               0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0});
    algorithms::graph_t graph(data);
    algorithms::GraphAlgoritms algoritms;
    auto result = algoritms.BreadthFirstSearch(graph, 1);
    std::size_t path[]{1, 2, 3, 4};
    for (int i = 0; i < result.size(); ++i) EXPECT_EQ(result[i], path[i]);
}

//    ########################
//    ##                    ##
//    ##     DEPTH_SEARCH   ##
//    ##                    ##
//    ########################

TEST(graph_depth_search3, trees) {
    Matrix<unsigned int> data({0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0});
    algorithms::graph_t graph(data);
    algorithms::GraphAlgoritms algoritms;
    auto result = algoritms.DepthFirstSearch(graph, 1);
    std::size_t path[]{1, 4, 2, 3};
    for (int i = 0; i < result.size(); ++i) EXPECT_EQ(result[i], path[i]);
}

TEST(graph_depth_search2, not_connecteds) {
    Matrix<unsigned int> data({0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0});
    algorithms::graph_t graph(data);
    algorithms::GraphAlgoritms algoritms;
    auto result = algoritms.DepthFirstSearch(graph, 1);
    std::size_t path[]{1, 3};
    for (int i = 0; i < result.size(); ++i) EXPECT_EQ(result[i], path[i]);
}

TEST(graph_depth_search1, treess) {
    Matrix<unsigned int> data({0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0});
    algorithms::graph_t graph(data);
    algorithms::GraphAlgoritms algoritms;
    auto result = algoritms.DepthFirstSearch(graph, 1);
    std::size_t path[]{1, 4, 2, 3};
    for (int i = 0; i < result.size(); ++i) EXPECT_EQ(result[i], path[i]);
}

//    #####################################
//    ##                                 ##
//    ##  SHORTEST_PATH_BETWEEN_VERTICES ##
//    ##                                 ##
//    #####################################

TEST(djikstra_algorithm, test_1) {
    Matrix<unsigned int> data({0, 7,  9, 0,  0, 14, 7,  0,  10, 15, 0, 0,
                               9, 10, 0, 11, 0, 2,  0,  15, 11, 0,  6, 0,
                               0, 0,  0, 6,  0, 9,  14, 0,  2,  0,  9, 0});
    algorithms::graph_t graph(data);
    algorithms::GraphAlgoritms algoritms;

    ASSERT_EQ(algoritms.GetShortestPathBetweenVertices(graph, 1, 6), 11);
}

TEST(djikstra_algorithm, test_2) {
    Matrix<unsigned int> data(
        {0, 4,  0, 0, 0, 0, 0,  8,  0, 4, 0, 8,  0, 0, 0, 0, 11, 0, 0, 8, 0,
         7, 0,  4, 0, 0, 2, 0,  0,  7, 0, 9, 14, 0, 0, 0, 0, 0,  0, 9, 0, 10,
         0, 0,  0, 0, 0, 4, 14, 10, 0, 2, 0, 0,  0, 0, 0, 0, 0,  2, 0, 1, 6,
         8, 11, 0, 0, 0, 0, 1,  0,  7, 0, 0, 2,  0, 0, 0, 6, 7,  0});
    algorithms::graph_t graph(data);
    algorithms::GraphAlgoritms algoritms;

    ASSERT_EQ(algoritms.GetShortestPathBetweenVertices(graph, 1, 5), 21);
}

//    ##########################################
//    ##                                      ##
//    ##  SHORTEST_PATHS_BETWEEN_ALL_VERTICES ##
//    ##                                      ##
//    ##########################################

TEST(floyd_warshall_algorithm, firstSit) {
    Matrix<unsigned int> data({0, 8, 3, 3, 0, 4, 4, 9, 0});
    algorithms::graph_t graph(data);
    algorithms::GraphAlgoritms algoritms;
    Matrix<unsigned int> result =
        algoritms.GetShortestPathsBetweenAllVertices(graph);
    ASSERT_EQ(0, result(0, 0));
    ASSERT_EQ(8, result(0, 1));
    ASSERT_EQ(3, result(0, 2));
    ASSERT_EQ(3, result(1, 0));
    ASSERT_EQ(0, result(1, 1));
    ASSERT_EQ(4, result(1, 2));
    ASSERT_EQ(4, result(2, 0));
    ASSERT_EQ(9, result(2, 1));
    ASSERT_EQ(0, result(2, 2));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
