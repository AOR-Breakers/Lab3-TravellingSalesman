#pragma once

#include "Selection.h"
#include <algorithm>
#include <random>

class TournamentSelection : public Selection {
private:
  int TournamentSize;

  std::random_device RandomDevice;
  std::default_random_engine Engine;

public:
  TournamentSelection() = delete;
  explicit TournamentSelection(int TournamentSize)
      : TournamentSize(TournamentSize) {
    Engine = std::default_random_engine(RandomDevice());
  };

  int select(const Population &P);

  std::vector<int> createTournament(const int SelectedSize);
};
