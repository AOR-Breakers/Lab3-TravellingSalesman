#pragma once

#include "../Chromosome.h"
#include "../Population.h"

class Selection {
public:
  virtual int select(const Population &P) = 0;

  virtual ~Selection() {}
};
