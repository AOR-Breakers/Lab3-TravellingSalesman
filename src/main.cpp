#include "Chromosome.h"
#include "GeneticAlgo.h"
#include "Graph.h"
#include "Population.h"
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
  std::string Filepath = "../data/raw/a280";
  Selection *SelectionAlg;
  Mutation *MutationAlg;
  Crossover *CrossoverAlg;

  SelectionAlg = new RankSelection(4, 2);
  // SelectionAlg = new TournamentSelection(50); // best 50
  //  SelectionAlg = new RouleteSelection();

  // MutationAlg = new SwapMutation();
  MutationAlg = new InversionMutation(); // best
  // MutationAlg = new DisplacementMutation();

  CrossoverAlg = new CycleCrossover(); // best
  //  CrossoverAlg = new OrderedCrossover();
  // CrossoverAlg = new PartiallyMappedCrossover();
  Graph ProblemGraph = Graph::fromFile(Filepath);

  GeneticAlgorithm GA(ProblemGraph, CrossoverAlg, MutationAlg, SelectionAlg);

  int PopulationSize = 100;
  double SimilarityTolerance = 0.001;
  double TargetSimilarity = 0.95;
  double MutationProbabilty = 0.5;
  int MaximalCyclesNumber = 500000;
  int MaximalCyclesWithoutNewBest = 10000;
  Chromosome Res = GA.start(PopulationSize, SimilarityTolerance,
                            TargetSimilarity, MutationProbabilty,
                            MaximalCyclesNumber, MaximalCyclesWithoutNewBest);

  std::vector<int> ConvertedPath = ProblemGraph.convertPath(Res.getPath());
  printVector(ConvertedPath);
  std::cout << Res.getFitness() << '\n';
}
