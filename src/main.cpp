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
  SelectionAlg = new RankSelection(10, 2);
  // SelectionAlg = new TournamentSelection(30);
  // SelectionAlg = new RouleteSelection();

  MutationAlg = new SwapMutation();
  // MutationAlg = new InversionMutation();
  //  MutationAlg = new DisplacementMutation();

  CrossoverAlg = new CycleCrossover();
  // CrossoverAlg = new OrderedCrossover();
  //  CrossoverAlg = new PartiallyMappedCrossover();
  Graph ProblemGraph = Graph::fromFile(Filepath);

  GeneticAlgorithm GA(ProblemGraph, CrossoverAlg, MutationAlg, SelectionAlg);

  int PopulationSize = 1000;
  double SimilarityTolerance = 0.001;
  double TargetSimilarity = 0.95;
  double MutationProbabilty = 0.7;
  int MaximalCyclesNumber = 1e6;
  Population Res =
      GA.start(PopulationSize, SimilarityTolerance, TargetSimilarity,
               MutationProbabilty, MaximalCyclesNumber);

  Chromosome Best = Res.getBest();
  printVector(Best.getPath());
  std::cout << Best.getFitness();
}
