#pragma once

#include "Mutation.h"
#include <algorithm>

class DisplacementMutation : public Mutation {
public:
  Chromosome mutate(const Graph &G, const Chromosome &C) {
    std::vector<int> Path = C.getPath();
    int Size = Path.size();
    int StartPos = rand() % Size;
    int Length = rand() % (Size - StartPos);

    std::vector<int> Segment(Path.begin() + StartPos,
                             Path.begin() + StartPos + Length);
    Path.erase(Path.begin() + StartPos, Path.begin() + StartPos + Length);

    int InsertPos = rand() % Size;
    Path.insert(Path.begin() + InsertPos, Segment.begin(), Segment.end());

    return Chromosome(G, Path);
  }
};
