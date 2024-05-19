#include "Chromosome.h"
#include "GeneticAlgo.h"
#include "Graph.h"
#include "Population.h"
#include "crossover/Crossover.h"
#include "crossover/CycleCrossover.h"
#include "mutation/Mutation.h"
#include "mutation/SwapMutation.h"
#include "selection/RankSelection.h"
#include "selection/RouletteSelection.h"
#include "selection/Selection.h"
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::string Filepath = "../data/raw/a280";
  // Selection *SelectionAlg = new RankSelection(10, 2);
  Selection *SelectionAlg = new RankSelection(4, 2);
  Mutation *MutationAlg = new SwapMutation();
  Crossover *CrossoverAlg = new CycleCrossover();
  Graph ProblemGraph = Graph::fromFile(Filepath);

  GeneticAlgorithm GA(ProblemGraph, CrossoverAlg, MutationAlg, SelectionAlg);

  int PopulationSize = 100;
  Population Res = GA.start(PopulationSize);

  Chromosome Best = Res.getBest();
  printVector(Best.getPath());
  std::cout << Best.getFitness();
}
