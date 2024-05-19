#pragma once

#include "Selection.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

class RankSelection : public Selection {
private:
  int RanksNumber;
  double SelectionPressure;
  std::vector<double> RankSelectionProbabilities;

  void calculateRankSelectionProbabilities() {
    for (int Iter = 1; Iter <= RanksNumber; ++Iter) {
      double Prob =
          1 / static_cast<double>(RanksNumber) *
          (SelectionPressure - (2 * SelectionPressure - 2) * (Iter - 1) /
                                   (static_cast<double>(RanksNumber - 1)));
      std::cout << Prob << '\n';
      RankSelectionProbabilities.push_back(Prob);
    }
  }

  std::random_device RandomDevice;
  std::default_random_engine Engine;
  std::uniform_real_distribution<double> DistReal;

public:
  RankSelection() = delete;
  RankSelection(RankSelection &) = delete;

  // Rank numbering goes from 0 to RanksNumber - 1
  explicit RankSelection(int RanksNumber, double SelectionPressure = 1.0)
      : RanksNumber(RanksNumber), SelectionPressure(SelectionPressure) {
    Engine = std::default_random_engine(RandomDevice());
    DistReal = std::uniform_real_distribution<double>(0, 1);
    calculateRankSelectionProbabilities();
  };

  int select(const Population &P) {
    std::vector<int> SortedByFitnessIdicies = sortByFitnessIndices(P);
    int PartSize = std::floor(P.size() / RanksNumber);
    int RandomRank = pickRank();
    int RandomIndex;
    if (RandomRank == RanksNumber - 1) {
      std::uniform_int_distribution<int> DistInt(0, P.size() -
                                                        RandomRank * PartSize);
      RandomIndex = DistInt(Engine);
    } else {

      std::uniform_int_distribution<int> DistInt(0, PartSize);
      RandomIndex = DistInt(Engine);
    }

    return SortedByFitnessIdicies[PartSize * RandomRank + RandomIndex];
  }

  int pickRank() {
    double RandomRealNumber = DistReal(Engine);
    double Offset = 0;
    for (int Index = 0; Index < RanksNumber; ++Index) {
      Offset += RankSelectionProbabilities[Index];
      if (RandomRealNumber < Offset) {
        return Index;
      }
    }
    return RanksNumber - 1;
  }

  std::vector<int> sortByFitnessIndices(const Population &P) {
    std::vector<Chromosome> Chromosomes = P.getChromosomes();
    std::vector<int> SortedByFitnessIdicies(Chromosomes.size());
    std::iota(std::begin(SortedByFitnessIdicies),
              std::end(SortedByFitnessIdicies), 0);

    std::sort(std::begin(SortedByFitnessIdicies),
              std::end(SortedByFitnessIdicies), [&Chromosomes](int X, int Y) {
                return Chromosomes[X].getFitness() <
                       Chromosomes[Y].getFitness();
              });
    return SortedByFitnessIdicies;
  }
};
