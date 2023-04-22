#pragma once

#include <memory>
#include <random>

#include "../algorithms/graph_algorithms.h"
#include "../graph/graph.h"

namespace algorithms {

using graph_t = graph::Graph;
using tsm_t = graph::TsmResult;  

const double kEvaporation = 0.64;
const unsigned short kNumber_iterations = 100;
const double kPheromones_start = 0.9;
const double kNumberPheromonesAnt = 4.;

class Ant {
   public:
    Ant(Matrix<double> &graph_distance, Matrix<double> &graph_pheromones,
        std::size_t &index_start, std::default_random_engine &e);

    void Run();
    void Reset(std::size_t &position);
    void SecretePheromones();
    tsm_t result() { return run_result_; }

   private:
    void Transition(std::vector<double> &transition_probabilities_vec,
                    std::vector<std::size_t> &where_can_go);
    void FillingConnectedPoints(std::vector<std::size_t> &where);
    void TransitionDesireCalculation(
        std::vector<double> &transition_probabilities_vec,
        std::vector<std::size_t> &where_can_go);
    void FillAvailablePlaces();

    std::default_random_engine &rand_engine_;
    Matrix<double> &graph_distance_;
    Matrix<double> &graph_pheromones_;
    std::vector<std::size_t> available_places_;
    tsm_t run_result_;
};

class Colony {
   public:
    explicit Colony(graph_t &graph);

    int Resolvable();
    void FindBestTravel();
    tsm_t result() const { return result_; }

   private:
    void CreateAnt(std::size_t index_start, std::default_random_engine &e);
    void EvaporatePheromones();

    tsm_t result_;
    Matrix<double> distance_;
    Matrix<double> pheromones_;
    std::vector<std::unique_ptr<Ant>> ants_;
    std::random_device rand_dev_;
    std::default_random_engine rand_engine_;
};

}  // namespace s21
