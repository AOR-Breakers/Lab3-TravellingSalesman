#pragma once

#include "Crossover.h"
#include <algorithm>
#include <map>
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

    std::vector<int> Child1Path(Size, -1);
    std::vector<int> Child2Path(Size, -1);

    if (StartPos > EndPos)
      std::swap(StartPos, EndPos);

    std::map<int, int> P1Map;
    std::map<int, int> P2Map;
    for (int Index = StartPos; Index <= EndPos; ++Index) {
      P1Map.insert({Child2Path[Index], Child1Path[Index]});
      P2Map.insert({Child1Path[Index], Child2Path[Index]});
      Child1Path[Index] = P2Path[Index];
      Child2Path[Index] = P1Path[Index];
    }

    for (int Index = 0; Index < Size; ++Index) {
      if (Index >= StartPos && Index <= EndPos)
        continue;

      int CurrentGene = P1Path[Index];
      while (P1Map.find(CurrentGene) != P1Map.end()) {
        CurrentGene = P1Map[CurrentGene];
      }

      Child1Path[Index] = CurrentGene;

      CurrentGene = P2Path[Index];
      while (P2Map.find(CurrentGene) != P2Map.end()) {
        CurrentGene = P2Map[CurrentGene];
      }

      Child2Path[Index] = CurrentGene;
    }

    Chromosome Child1 = Chromosome(G, Child1Path);
    Chromosome Child2 = Chromosome(G, Child2Path);
    return std::make_pair(Child1, Child2);
  }
};
