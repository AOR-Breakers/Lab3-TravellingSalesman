#pragma once

#include "Crossover.h"
#include <algorithm>
#include <iostream>
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
    if (StartPos == EndPos) {
      Chromosome Child1 = Chromosome(G, P1Path);
      Chromosome Child2 = Chromosome(G, P2Path);
      return std::make_pair(Child1, Child2);
    }

    std::vector<int> Child1Path(Size, -1);
    std::vector<int> Child2Path(Size, -1);

    if (StartPos > EndPos)
      std::swap(StartPos, EndPos);

    std::copy(P1Path.begin() + StartPos, P1Path.begin() + EndPos + 1,
              Child1Path.begin() + StartPos);

    std::copy(P2Path.begin() + StartPos, P2Path.begin() + EndPos + 1,
              Child2Path.begin() + StartPos);

    // 4 2 5 | 1 6 8 | 3 7
    // 4 2 5 | 1 6 8 | 7 3
    // 8 6 1 | 5 2 4 | 7 3
    // 3 7 4 | 2 5 1 | 6 8
    std::reverse(P1Path.begin() + EndPos + 1, P1Path.end());
    std::reverse(P1Path.begin(), P1Path.begin() + EndPos + 1);
    std::reverse(P1Path.begin(), P1Path.end());

    std::reverse(P2Path.begin() + EndPos + 1, P2Path.end());
    std::reverse(P2Path.begin(), P2Path.begin() + EndPos + 1);
    std::reverse(P2Path.begin(), P2Path.end());

    int J1 = (EndPos + 1) % Size;
    for (int Iter = 0; J1 < StartPos || EndPos <= J1; ++Iter) {
      if (std::find(Child1Path.begin() + StartPos,
                    Child1Path.begin() + EndPos + 1,
                    P2Path[Iter]) != Child1Path.begin() + EndPos + 1) {
        continue;
      }

      Child1Path[J1] = P2Path[Iter];
      J1 = (J1 + 1) % Size;
    }

    int J2 = (EndPos + 1) % Size;
    for (int Iter = 0; J2 < StartPos || EndPos <= J2; ++Iter) {
      if (std::find(Child2Path.begin() + StartPos,
                    Child2Path.begin() + EndPos + 1,
                    P1Path[Iter]) != Child2Path.begin() + EndPos + 1) {
        continue;
      }
      Child2Path[J2] = P1Path[Iter];
      J2 = (J2 + 1) % Size;
    }

    Chromosome Child1 = Chromosome(G, Child1Path);
    Chromosome Child2 = Chromosome(G, Child2Path);
    return std::make_pair(Child1, Child2);
  }
};
