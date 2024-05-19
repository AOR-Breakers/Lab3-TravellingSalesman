#include <random>
#pragma once

#include "Selection.h"

class RouleteSelection : public virtual Selection {

  std::random_device RandomDevice;
  std::default_random_engine Engine;
  std::uniform_real_distribution<double> DistReal;

public:
  RouleteSelection(RouleteSelection &) = delete;
  RouleteSelection() {
    Engine = std::default_random_engine(RandomDevice());
    DistReal = std::uniform_real_distribution<double>(0, 1);
  }

  int select(const Population &P);
};
