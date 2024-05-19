#pragma once

#include "Mutation.h"
#include <algorithm>

class InversionMutation : public Mutation {
public:
  Chromosome mutate(const Graph &G, const Chromosome &C) {
    std::vector<int> Path = C.getPath();
    int Size = Path.size();
    int StartPos = rand() % Size;
    int EndPos = rand() % Size;

    if (StartPos > EndPos)
      std::swap(StartPos, EndPos);

    std::reverse(Path.begin() + StartPos, Path.begin() + EndPos + 1);

    return Chromosome(G, Path);
  }
};
