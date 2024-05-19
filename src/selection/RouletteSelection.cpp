#include "RouletteSelection.h"
#include <iostream>
#include <random>

int RouleteSelection::select(const Population &P) {
  std::vector<Chromosome> Chromosomes = P.getChromosomes();
  std::vector<double> Probabilites = P.getRouleteProbabilities();

  double RandomRealNumber = DistReal(Engine);
  double Offset = 0;
  for (int Index = 0; Index < P.size(); ++Index) {
    Offset += Probabilites[Index];
    if (RandomRealNumber < Offset) {
      return Index;
    }
  }
  return P.size() - 1;
}
