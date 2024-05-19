#pragma once

#include "Crossover.h"
#include <algorithm>
#include <utility>

class OrderedCrossover : public Crossover {
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

    std::copy(P1Path.begin() + StartPos, P1Path.begin() + EndPos + 1,
              Child1Path.begin() + StartPos);

    std::copy(P2Path.begin() + StartPos, P2Path.begin() + EndPos + 1,
              Child2Path.begin() + StartPos);

    int J1 = (EndPos + 1) % Size;
    int J2 = (EndPos + 1) % Size;

    for (int Iter = 0; Iter < Size; ++Iter) {
      if (Iter >= StartPos && Iter <= EndPos)
        continue;

      int NextIdx1 = (EndPos + 1 + Iter) % Size;
      int NextIdx2 = (EndPos + 1 + Iter) % Size;

      while (std::find(Child1Path.begin() + StartPos,
                       Child1Path.begin() + EndPos + 1,
                       P2Path[NextIdx1]) != Child1Path.begin() + EndPos + 1)
        NextIdx1 = (EndPos + 1 + NextIdx1) % Size;

      while (std::find(Child2Path.begin() + StartPos,
                       Child2Path.begin() + EndPos + 1,
                       P1Path[NextIdx2]) != Child2Path.begin() + EndPos + 1)
        NextIdx2 = (EndPos + 1 + NextIdx2) % Size;

      Child1Path[J1] = P2Path[NextIdx1];
      Child2Path[J2] = P1Path[NextIdx2];

      J1 = (J1 + 1) % Size;
      J2 = (J2 + 1) % Size;
    }

    Chromosome Child1 = Chromosome(G, Child1Path);
    Chromosome Child2 = Chromosome(G, Child2Path);
    return std::make_pair(Child1, Child2);
  }
};
