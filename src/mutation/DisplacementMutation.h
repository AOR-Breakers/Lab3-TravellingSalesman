#pragma once

#include "Mutation.h"
#include <algorithm>
#include <iterator>

class DisplacementMutation : public Mutation {
public:
  Chromosome mutate(const Graph &G, const Chromosome &C) {
    std::vector<int> Path = C.getPath();
    int Size = Path.size();
    int StartPos = rand() % (Size - 1) + 1;
    int Length = rand() % (std::min(Size - StartPos, StartPos));

    std::reverse(std::begin(Path) + StartPos - Length,
                 std::begin(Path) + StartPos + Length);
    std::reverse(std::begin(Path) + StartPos - Length,
                 std::begin(Path) + StartPos);

    std::reverse(std::begin(Path) + StartPos,
                 std::begin(Path) + StartPos + Length);

    return Chromosome(G, Path);
  }
};
