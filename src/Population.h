#pragma once

#include "Chromosome.h"
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

class Population {
  std::vector<Chromosome> Chromosomes;
  int FitnessSum = 0;
  int Size;
  double AverageFitness = 0;
  double VarianceFitness = 0;

  std::vector<double> RouleteProbabiliets;

  double calculateAverageFitness() {
    return static_cast<double>(FitnessSum) / static_cast<double>(Size);
  }

  double calculateVarianceFitness() {
    double Variance = 0;
    for (auto &C : Chromosomes) {
      double D = (static_cast<double>(C.getFitness()) - AverageFitness);
      Variance += D * D;
    }

    return Variance / static_cast<double>(Size - 1);
  }

public:
  Population() = delete;

  Population(std::vector<Chromosome> Chromosomes)
      : Chromosomes(Chromosomes), Size(Chromosomes.size()),
        RouleteProbabiliets(Chromosomes.size()) {

    FitnessSum = std::accumulate(
        Chromosomes.begin(), Chromosomes.end(), 0,
        [&](int Sum, const Chromosome &C) { return Sum + C.getFitness(); });

    for (int Index = 0; Index < Size; ++Index) {
      RouleteProbabiliets[Index] =
          static_cast<double>(Chromosomes[Index].getFitness()) /
          static_cast<double>(FitnessSum);
    }

    AverageFitness = calculateAverageFitness();
    VarianceFitness = calculateVarianceFitness();
  }

  double size() const { return Size; }

  std::vector<double> getRouleteProbabilities() const {
    return RouleteProbabiliets;
  }

  std::vector<Chromosome> getChromosomes() const { return Chromosomes; }

  Chromosome get(int Index) const { return Chromosomes[Index]; }

  Chromosome getBest() const {
    Chromosome Best = Chromosomes[0];
    for (auto &C : Chromosomes) {
      if (C.getFitness() < Best.getFitness()) {
        Best = C;
      }
    }
    return Best;
  }

  double getAverageFitness() const { return AverageFitness; }

  double getVarianceFitness() const { return VarianceFitness; }

  double getStdFitness() const { return std::sqrt(VarianceFitness); }
};
