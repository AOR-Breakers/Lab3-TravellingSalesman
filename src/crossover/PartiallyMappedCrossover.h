#pragma once

#include "Crossover.h"
#include <algorithm>
#include <unordered_set>
#include <utility>

class PartiallyMappedCrossover : public Crossover {
public:
  std::pair<Chromosome, Chromosome>
  crossover(const Graph &G, const Chromosome &P1, const Chromosome &P2) {
    std::vector<int> P1Path = P1.getPath();
    std::vector<int> P2Path = P2.getPath();

    int Size = P1Path.size();
    int StartPos = rand() % Size;
    int EndPos = rand() % Size;

    std::vector<int> Child1Path;
    std::vector<int> Child2Path;

    if (StartPos > EndPos)
      std::swap(StartPos, EndPos);

    for (int Index = StartPos; Index <= EndPos; ++Index) {
      Child1Path[Index] = P2Path[Index];
      Child2Path[Index] = P1Path[Index];
    }

    std::unordered_set<int> MappedGenes(Child1Path.begin() + StartPos,
                                        Child1Path.begin() + EndPos + 1);

    for (int Index = 0; Index < Size; ++Index) {
      if (Index >= StartPos && Index <= EndPos)
        continue;

      int CurrentGene = P1Path[Index];
      while (MappedGenes.find(CurrentGene) != MappedGenes.end())
        CurrentGene = P1Path[std::distance(
            P1Path.begin(),
            std::find(P2Path.begin(), P2Path.end(), CurrentGene))];

      Child1Path[Index] = CurrentGene;

      CurrentGene = P2Path[Index];
      while (MappedGenes.find(CurrentGene) != MappedGenes.end())
        CurrentGene = P2Path[std::distance(
            P2Path.begin(),
            std::find(P1Path.begin(), P1Path.end(), CurrentGene))];

      Child2Path[Index] = CurrentGene;
    }

    Chromosome Child1 = Chromosome(G, Child1Path);
    Chromosome Child2 = Chromosome(G, Child2Path);
    return std::make_pair(Child1, Child2);
  }
};
