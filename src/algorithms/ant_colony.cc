#include "ant_colony.h"

namespace algorithms {

Ant::Ant(Matrix<double> &graph_distance, Matrix<double> &graph_pheromones,
         std::size_t &index_start, std::default_random_engine &e)
    : graph_distance_(graph_distance),
      graph_pheromones_(graph_pheromones),
      rand_engine_(e),
      run_result_({}) {
    run_result_.vertices_.push_back(index_start);
    FillAvailablePlaces();
}

void Ant::FillAvailablePlaces() {
    for (std::size_t i = 0; i < graph_distance_.getColumn(); ++i) {
        if (i != run_result_.vertices_[0]) {
            available_places_.push_back(i);
        }
    }
}

void Ant::FillingConnectedPoints(std::vector<std::size_t> &where) {
    for (auto i = available_places_.begin(); i != available_places_.end();
         ++i) {
        if (graph_distance_(run_result_.vertices_.back(), *i) > 0) {
            where.push_back(*i);
        }
    }
}

void Ant::TransitionDesireCalculation(
    std::vector<double> &transition_probabilities_vec,
    std::vector<std::size_t> &where_can_go) {
    double sum_all_desires = 0;

    for (auto i = where_can_go.begin(); i != where_can_go.end(); ++i) {
        sum_all_desires +=
            graph_pheromones_(run_result_.vertices_.back(), *i) *
            (1 / graph_distance_(run_result_.vertices_.back(), *i));
    }

    for (auto j = where_can_go.begin(); j != where_can_go.end(); ++j) {
        double desire =
            graph_pheromones_(run_result_.vertices_.back(), *j) *
            (double)(1 / graph_distance_(run_result_.vertices_.back(), *j));

        transition_probabilities_vec.push_back(desire / sum_all_desires);
    }
}

void Ant::Transition(std::vector<double> &transition_probabilities_vec,
                     std::vector<std::size_t> &where_can_go) {
    std::uniform_real_distribution<double> distr(0., 1.);
    double random_choice = distr(rand_engine_);
    double choise_probability = 0;
    for (std::size_t i = 0; i < transition_probabilities_vec.size(); ++i) {
        choise_probability += transition_probabilities_vec[i];
        if (random_choice <= choise_probability) {
            run_result_.distance_ +=
                graph_distance_(run_result_.vertices_.back(), where_can_go[i]);
            run_result_.vertices_.push_back(where_can_go[i]);
            available_places_.erase(available_places_.begin() + i);
            break;
        }
    }
}

void Ant::Run() {
    for (std::size_t k = 0; k < graph_distance_.getColumn(); ++k) {
        if (k == graph_distance_.getColumn() - 1)
            available_places_.push_back(run_result_.vertices_[0]);
        std::vector<double> trans_prob{};
        std::vector<std::size_t> where_can_go{};
        FillingConnectedPoints(where_can_go);
        TransitionDesireCalculation(trans_prob, where_can_go);
        Transition(trans_prob, where_can_go);
    }
}

void Ant::SecretePheromones() {
    double pheromone = kNumberPheromonesAnt / run_result_.distance_;
    for (std::size_t i = 0; i < run_result_.vertices_.size() - 1; ++i) {
        graph_pheromones_(run_result_.vertices_[i],
                          run_result_.vertices_[i + 1]) +=
            pheromone * graph_distance_(run_result_.vertices_[i],
                                        run_result_.vertices_[i + 1]);
    }
}

void Ant::Reset(std::size_t &position) {
    available_places_.clear();
    run_result_.distance_ = 0;
    run_result_.vertices_.clear();
    run_result_.vertices_.push_back(position);
    FillAvailablePlaces();
}

Colony::Colony(graph_t &graph) : result_({}) {
    size_t size = graph.GetSize();
    distance_.setRows(size);
    distance_.setColumn(size);
    pheromones_.setRows(size);
    pheromones_.setColumn(size);

    for (auto i = 0; i < size; i++) {
        for (auto j = 0; j < size; j++) {
            distance_(i, j) = graph.GetAdjacencyMatrix()(i, j);
        }
    }

    for (auto i = 0; i < size; i++) {
        for (auto j = 0; j < size; j++) {
            if (graph.GetAdjacencyMatrix()(i, j) > 0) {
                pheromones_(i, j) = kPheromones_start;
            }
        }
    }
}

int Colony::Resolvable() {
    size_t size = distance_.getColumn();
    int res = 0;

    for (std::size_t i = 0; i < size; i++) {
        for (std::size_t j = 0; j < size; j++) {
            if (distance_(i, j) != distance_(j, i) ||
                (i != j && distance_(i, j) == 0)) {
                res = 1;
                break;
            }
        }
    }
    return res;
}

void Colony::CreateAnt(std::size_t index_start, std::default_random_engine &e) {
    ants_.push_back(
        std::make_unique<Ant>(distance_, pheromones_, index_start, e));
}

void Colony::EvaporatePheromones() {
    for (std::size_t i = 0; i < pheromones_.getRows(); i++) {
        for (std::size_t j = 0; j < pheromones_.getColumn(); j++) {
            pheromones_(i, j) *= kEvaporation;
        }
    }
}

void Colony::FindBestTravel() {
    result_.distance_ = (int)INFINITY;
    for (size_t l = 0; l < kNumber_iterations * distance_.getColumn();
         ++l) {
        for (std::size_t i = 0; i < distance_.getColumn(); ++i) {
            CreateAnt(i, rand_engine_);
            ants_[i]->Run();

            if (ants_[i]->result().distance_ < result_.distance_) {
                result_ = ants_[i]->result();
                l = 0;
            }
        }
        EvaporatePheromones();
        for (std::size_t i = 0; i < distance_.getColumn(); ++i) {
            ants_[i]->SecretePheromones();
            ants_[i]->Reset(i);
        }
    }
}

}  // namespace s21
