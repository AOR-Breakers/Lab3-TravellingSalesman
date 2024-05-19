#pragma once
#include "Chromosome.h"
#include "Graph.h"
#include "Population.h"
#include "crossover/Crossover.h"
#include "mutation/Mutation.h"
#include "selection/Selection.h"
#include <algorithm>
#include <iostream>
#include <random>

class GeneticAlgorithm {
private:
  const Graph &ProblemGraph;
  Crossover *CrossoverAlg;
  Mutation *MutationAlg;
  Selection *SelectionAlg;

  std::random_device RandomDevice;
  std::default_random_engine Engine;
  std::uniform_real_distribution<double> DistProb;

  Population generateFirstPopulation(int PopulationSize) {
    std::vector<Chromosome> Chromosomes;
    for (int Iter = 0; Iter < PopulationSize; ++Iter) {
      std::vector<int> Path(ProblemGraph.verticeCount());
      std::iota(std::begin(Path), std::end(Path), 0);
      std::shuffle(Path.begin(), Path.end(), Engine);

      Chromosomes.push_back(Chromosome(ProblemGraph, Path));
    }
    return Population(Chromosomes);
  }

public:
  GeneticAlgorithm() = delete;

  explicit GeneticAlgorithm(const Graph &G, Crossover *CrossoverAlg,
                            Mutation *MutationAlg, Selection *SelectionAlg)

      : ProblemGraph(G), CrossoverAlg(CrossoverAlg), MutationAlg(MutationAlg),
        SelectionAlg(SelectionAlg) {
    Engine = std::default_random_engine(RandomDevice());
    DistProb = std::uniform_real_distribution<double>(0, 1);
  };

  Population start(const int PopulationSize,
                   const double SimilarityTolerance = 0.05,
                   const double TargetSimilarity = 0.95,
                   const double MutationProbabilty = 0.5,
                   const int MaximalCyclesNumber = 1e6) {
    double CurrentSimilarity = 0.0;

    Population CurrentPopulation = generateFirstPopulation(PopulationSize);

    for (int64_t Cycle = 0;
         CurrentSimilarity < TargetSimilarity && Cycle < MaximalCyclesNumber;
         ++Cycle) {

      std::vector<Chromosome> Chromosomes;
      for (int Iter = 0; Iter < PopulationSize / 2; ++Iter) {

        int Parent1Index = SelectionAlg->select(CurrentPopulation);
        int Parent2Index = SelectionAlg->select(CurrentPopulation);

        std::pair<Chromosome, Chromosome> CrossoverRes =
            CrossoverAlg->crossover(ProblemGraph,
                                    CurrentPopulation.get(Parent1Index),
                                    CurrentPopulation.get(Parent2Index));

        Chromosome Child1 = CrossoverRes.first, Child2 = CrossoverRes.second;

        double ProbMutateChild1 = DistProb(Engine);
        double ProbMutateChild2 = DistProb(Engine);

        if (ProbMutateChild1 < MutationProbabilty) {
          Child1 = MutationAlg->mutate(ProblemGraph, Child1);
        }
        if (ProbMutateChild2 < MutationProbabilty) {
          Child2 = MutationAlg->mutate(ProblemGraph, Child2);
        }

        Chromosomes.push_back(Child1);
        Chromosomes.push_back(Child2);

        /*int minIndex = 0;
        double minFitness = population.chromosomes[0].fitness;
        for (int i = 0; i < population.chromosomes.size(); ++i) {
            if (population.chromosomes[i].fitness < minFitness) {
                minIndex = i;
                minFitness = population.chromosomes[i].fitness;
            }
        }

        if (Child1.fitness > Child2.fitness) {
            population.chromosomes[minIndex] = Child2;
        } else {
            population.chromosomes[minIndex] = Child1;
        }*/
      }
      CurrentPopulation = Population(Chromosomes);

      CurrentSimilarity =
          percentageOfSimilarFitness(CurrentPopulation, SimilarityTolerance);
      if (Cycle % 10 == 0) {
        Chromosome C = CurrentPopulation.getBest();
        std::cout << "Cycles: " << Cycle << '\n';
        std::cout << "Similarity: " << CurrentSimilarity << '\n';
        std::cout << C.getFitness() << '\n';
        std::cout << '\n';
      }
    }

    return CurrentPopulation;
  }

  double similarity(double X, double Y) {
    return 1 - std::abs(X - Y) / std::max(X, Y);
  }

  double similarityFitness(const Chromosome &C1, const Chromosome &C2) {
    return similarity(C1.getFitness(), C2.getFitness());
  }

  double percentageOfSimilarFitness(const Population &P,
                                    double SimilarityTolerance) {
    double Size = P.size();
    double Simillar = 0;
    for (int IndexI = 0; IndexI < Size - 1; ++IndexI) {
      for (int IndexJ = IndexI + 1; IndexJ < Size; ++IndexJ) {
        if (1 - similarityFitness(P.get(IndexI), P.get(IndexJ)) <=
            SimilarityTolerance) {
          Simillar++;
        }
      }
    }
    return Simillar / (Size * (Size - 1) / 2);
  }
};
