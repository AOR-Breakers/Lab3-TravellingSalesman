#pragma once

#include "Chromosome.h"
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>

class Population {
  std::vector<Chromosome> Chromosomes;
  int FitnessSum = 0;
  int Size;
  std::vector<double> RouleteProbabiliets;

public:
  Population() = delete;

  Population(std::vector<Chromosome> Chromosomes)
      : Chromosomes(Chromosomes), Size(Chromosomes.size()),
        RouleteProbabiliets(Chromosomes.size()) {

    FitnessSum = std::accumulate(
        Chromosomes.begin(), Chromosomes.end(), 0,
        [&](int Sum, const Chromosome &C) { return Sum + C.getFitness(); });
    std::cout << FitnessSum << '\n';

    for (int Index = 0; Index < Size; ++Index) {
      std::cout << "Fitness: " << Chromosomes[Index].getFitness() << '\n';
      RouleteProbabiliets[Index] =
          static_cast<double>(Chromosomes[Index].getFitness()) /
          static_cast<double>(FitnessSum);
    }
  }

  double size() const { return Size; }

  std::vector<double> getRouleteProbabilities() const {
    return RouleteProbabiliets;
  }

  std::vector<Chromosome> getChromosomes() const { return Chromosomes; }

  void addChromosome(const Chromosome C) { Chromosomes.push_back(C); }
  Chromosome get(int Index) const { return Chromosomes[Index]; }
  void replace(int Index, Chromosome C) { Chromosomes[Index] = C; }

  Chromosome getBest() {
    Chromosome Best = Chromosomes[0];
    for (auto &C : Chromosomes) {
      if (C.getFitness() < Best.getFitness()) {
        Best = C;
      }
    }
    return Best;
  }
};
