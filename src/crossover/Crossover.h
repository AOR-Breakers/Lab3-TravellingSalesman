#pragma once

#include "../Chromosome.h"

class Crossover {
public:
  virtual std::pair<Chromosome, Chromosome>
  crossover(const Graph &G, const Chromosome &P1, const Chromosome &P2) = 0;

  virtual ~Crossover(){};
};
