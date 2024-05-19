add_library(genetic GeneticAlgo.h Graph.h Population.h Chromosome.h Graph.cpp)

add_subdirectory(mutation)
add_subdirectory(crossover)
add_subdirectory(selection)
