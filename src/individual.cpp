#include <algorithm>
#include <random>
#include <utility>
#include "individual.h"


namespace AI_homework {
namespace TSP_genetic_algorithm {

Individual::Individual() : path(),
                           cost(0.0),
                           fitness(0.0)
{
}

void Individual::Crossover(Individual &mate, std::mt19937 &generator)
{
    std::uniform_int_distribution<int> distribution(1, path.size() - 1);
    int crossover_point = distribution(generator);

    Individual child1, child2;

    child1.path.assign(path.begin(), path.begin() + crossover_point);
    for (int city_index : mate.path)
    {
        if (std::find(child1.path.begin(), child1.path.end(), city_index) ==
            child1.path.end())
            child1.path.push_back(city_index);
    }

    child2.path.assign(mate.path.begin(), mate.path.begin() + crossover_point);
    for (int city_index : path)
    {
        if (std::find(child2.path.begin(), child2.path.end(), city_index) ==
            child2.path.end())
            child2.path.push_back(city_index);
    }

    path = std::move(child1.path);
    mate.path = std::move(child2.path);
}

void Individual::Mutate(std::mt19937 &generator)
{
    std::uniform_int_distribution<int> distribution(1, path.size() - 1);

    int position_1 = distribution(generator);
    int position_2;
    while ((position_2 = distribution(generator)) == position_1)
        continue;

    std::swap(path[position_1], path[position_2]);
}

}  // namespace TSP_genetic_algorithm
}  // namespace AI_homework
