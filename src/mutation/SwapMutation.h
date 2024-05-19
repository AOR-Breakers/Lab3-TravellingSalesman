#pragma once

#include "Mutation.h"

class SwapMutation : public Mutation {
public:
  Chromosome mutate(const Graph &G, const Chromosome &C) {
    std::vector<int> Path = C.getPath();
    int Size = Path.size();
    int Pos1 = rand() % Size;
    int Pos2 = rand() % Size;

    std::swap(Path[Pos1], Path[Pos2]);
    return Chromosome(G, Path);
  }
};
