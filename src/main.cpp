#include "Chromosome.h"
#include "GeneticAlgo.h"
#include "Graph.h"
#include "Population.h"
#include <chrono>
//
#include "crossover/Crossover.h"
#include "crossover/CycleCrossover.h"
#include "crossover/OrderedCrossover.h"
#include "crossover/PartiallyMappedCrossover.h"
//
#include "mutation/DisplacementMutation.h"
#include "mutation/InversionMutation.h"
#include "mutation/Mutation.h"
#include "mutation/SwapMutation.h"
//
#include "selection/RankSelection.h"
#include "selection/RouletteSelection.h"
#include "selection/Selection.h"
#include "selection/TournamentSelection.h"
//
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::string Filepath = "../data/raw/bays29";
  Selection *SelectionAlg;
  Mutation *MutationAlg;
  Crossover *CrossoverAlg;

  // SelectionAlg = new RankSelection(4, 2);
  SelectionAlg = new TournamentSelection(50);
  // SelectionAlg = new RouleteSelection();

  // MutationAlg = new SwapMutation();
  MutationAlg = new InversionMutation();
  //  MutationAlg = new DisplacementMutation();

  // CrossoverAlg = new CycleCrossover();
  CrossoverAlg = new OrderedCrossover();
  //  CrossoverAlg = new PartiallyMappedCrossover();

  Graph ProblemGraph = Graph::fromFile(Filepath);

  GeneticAlgorithm GA(ProblemGraph, CrossoverAlg, MutationAlg, SelectionAlg);

  int PopulationSize = 100;
  double SimilarityTolerance = 0.1; // use std
  double TargetSimilarity = 0.95;
  double MutationProbabilty = 0.5;
  int MaximalCyclesNumber = 500000;
  int MaximalCyclesWithoutNewBest = 10000;
  std::chrono::steady_clock::time_point BeginTime =
      std::chrono::steady_clock::now();
  Chromosome Res = GA.start(PopulationSize, SimilarityTolerance,
                            TargetSimilarity, MutationProbabilty,
                            MaximalCyclesNumber, MaximalCyclesWithoutNewBest);

  std::chrono::steady_clock::time_point EndTime =
      std::chrono::steady_clock::now();
  std::vector<int> ConvertedPath = ProblemGraph.convertPath(Res.getPath());
  std::cout << "Vertices: " << ProblemGraph.verticeCount() << '\n';
  std::cout << "Cycles to find solution: " << GA.getCycles() << '\n';
  std::cout << "Best found path: " << '\n';
  printVector(ConvertedPath);
  std::cout << "Fitness: " << Res.getFitness() << '\n';
  auto AlgoTime = EndTime - BeginTime;
  std::cout
      << "Algo time: "
      << std::chrono::duration_cast<std::chrono::minutes>(AlgoTime).count()
      << ':'
      << std::chrono::duration_cast<std::chrono::seconds>(AlgoTime).count() % 60
      << '.'
      << std::chrono::duration_cast<std::chrono::milliseconds>(AlgoTime)
                 .count() %
             1000;
}
