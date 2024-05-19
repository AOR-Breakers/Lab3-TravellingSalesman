#pragma once

#include "Crossover.h"
#include <algorithm>
#include <utility>

class CycleCrossover : public Crossover {
public:
  std::pair<Chromosome, Chromosome>
  crossover(const Graph &G, const Chromosome &P1, const Chromosome &P2) {
    std::vector<int> P1Path = P1.getPath();
    std::vector<int> P2Path = P2.getPath();

    int Size = P1Path.size();
    std::vector<int> Child1Path(Size);
    std::vector<int> Child2Path(Size);

    std::vector<bool> Visited(Size, false);

    int Current = P1Path[0];
    int CurrentIndex = 0;

    while (!Visited[Current]) {
      Child1Path[CurrentIndex] = Current;
      Visited[Current] = true;
      CurrentIndex =
          std::distance(P1Path.begin(), std::find(P1Path.begin(), P1Path.end(),
                                                  P2Path[CurrentIndex]));
      Current = P1Path[CurrentIndex];
    }

    for (int Index = 0; Index < Size; ++Index) {
      if (!Visited[P1Path[Index]]) {
        Child1Path[Index] = P1Path[Index];
        Child2Path[Index] = P2Path[Index];
      } else {
        Child2Path[Index] = P1Path[Index];
        Child1Path[Index] = P2Path[Index];
      }
    }

    Chromosome Child1 = Chromosome(G, Child1Path);
    Chromosome Child2 = Chromosome(G, Child2Path);
    return std::make_pair(Child1, Child2);
  }
};
