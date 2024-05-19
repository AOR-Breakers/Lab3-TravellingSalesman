#include "TournamentSelection.h"
#include <random>

int TournamentSelection::select(const Population &P) {
  std::vector<Chromosome> Chromosomes = P.getChromosomes();
  int Size = P.getChromosomes().size();
  std::vector<int> Tournament = createTournament(Size);
  int SelectedChromosome = Tournament[0];
  for (auto &C : Tournament) {
    if (Chromosomes[C].getFitness() <
        Chromosomes[SelectedChromosome].getFitness()) {
      SelectedChromosome = C;
    }
  }

  return SelectedChromosome;
}

std::vector<int>
TournamentSelection::createTournament(const int PopulationSize) {
  std::uniform_int_distribution<int> DistInt(0, PopulationSize - 1);
  std::vector<int> SelectedIndecies;
  while (SelectedIndecies.size() != TournamentSize) {
    int RandomIndex = DistInt(Engine);
    if (std::find(SelectedIndecies.begin(), SelectedIndecies.end(),
                  RandomIndex) != SelectedIndecies.end()) {
      continue;
    }
    SelectedIndecies.push_back(RandomIndex);
  }
  return SelectedIndecies;
}
