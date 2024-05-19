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
    std::vector<std::vector<Chromosome>> Splitted = splitByRanks(P);
    int RandomRank = pickRank();
    int SplittedPartSize = Splitted[RandomRank].size();
    int PartSize = std::floor(P.size() / RanksNumber);
    std::uniform_int_distribution<int> DistInt(0, SplittedPartSize - 1);
    int RandomIndex = DistInt(Engine);

    return PartSize * RandomRank + RandomIndex;
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

  std::vector<std::vector<Chromosome>> splitByRanks(const Population &P) {
    std::vector<Chromosome> Chromosomes = P.getChromosomes();
    std::sort(Chromosomes.begin(), Chromosomes.end(),
              [](const Chromosome &A, const Chromosome &B) {
                return A.getFitness() < B.getFitness();
              });

    int PartSize = std::floor(P.size() / RanksNumber);
    std::vector<std::vector<Chromosome>> ChromosomesSplitted(RanksNumber);
    for (int Rank = 0; Rank < RanksNumber - 1; ++Rank) {
      for (int Index = (Rank)*PartSize; Index < (Rank + 1) * PartSize;
           ++Index) {
        ChromosomesSplitted[Rank].push_back(Chromosomes[Index]);
      }
    }
    for (int Index = (RanksNumber - 1) * PartSize; Index < Chromosomes.size();
         ++Index) {

      ChromosomesSplitted[RanksNumber - 1].push_back(Chromosomes[Index]);
    }
    return ChromosomesSplitted;
  }
};
