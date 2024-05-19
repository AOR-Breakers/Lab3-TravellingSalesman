#pragma once

#include "Graph.h"
#include <vector>

class Chromosome {
private:
  std::vector<int> Path;
  int Size;
  int Fitness;

public:
  Chromosome(){};

  Chromosome(const Graph &G, std::vector<int> Path)
      : Path(Path), Size(Path.size()) {
    Fitness = G.fitnessFunction(Path);
  }

  const std::vector<int> &getPath() const { return Path; }
  int getFitness() const { return Fitness; }

  void setPath(const std::vector<int> &NewPath, Graph &G) {
    Path = NewPath;
    Size = Path.size();
    Fitness = G.fitnessFunction(NewPath);
  }
};
