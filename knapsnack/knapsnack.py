import time
import random
from tabulate import tabulate
from typing import List, Tuple

import numpy as np

MAGIC_NUMBER = 95
KNAPSACK_BENCHMARKS_PATH = 'knapsack'


def selection_function(chromosomes: List[List[int]], fitness: List[Tuple[int, int]]) -> List[List[int]]:
    size_t = len(chromosomes)
    fitness.sort(reverse=True, key=lambda x: x[1])
    reordered_chroms = [chromosomes[ind[0]] for ind in fitness]

    first_part = random.choices(reordered_chroms[0: size_t // 4],
                                k=int(size_t // 4 * 0.5))
    second_part = random.choices(reordered_chroms[size_t // 4: size_t // 2],
                                 k=int(size_t // 4 * 0.3))
    third_part = random.choices(reordered_chroms[size_t // 2: 3 * size_t // 4],
                                k=int(size_t // 4 * 0.15))
    fourth_part = random.choices(reordered_chroms[3 * size_t // 4:],
                                 k=int(size_t // 4 * 0.05))

    return first_part + second_part + third_part + fourth_part


def fitness_function(chromosome: List[int], capacity: int,
                     items_weight: np.array, items_cost: np.array) -> np.array:
    total_weight = np.sum(items_weight * chromosome)
    total_benefit = np.sum(items_cost * chromosome)

    while total_weight > capacity:
        nonzero_chrom = np.nonzero(chromosome)[0]
        chromosome[nonzero_chrom[np.random.randint(low=0, high=len(nonzero_chrom))]] = 0

        total_weight = np.sum(chromosome * items_weight)
        total_benefit = np.sum(chromosome * items_cost)

    return total_benefit


def crossover_function(chromosomes: List[List[int]]) -> List[List[int]]:
    size_t = len(chromosomes[0])
    rand_ind = np.random.randint(low=1, high=size_t - 1)

    for ind in range(0, size_t - 1, 2):
        chromosomes[ind][rand_ind:], chromosomes[ind + 1][rand_ind:] = \
            chromosomes[ind + 1][rand_ind:], chromosomes[ind][rand_ind:]

    return mutation_function(chromosomes)


def mutation_function(chromosomes: List[List[int]]) -> List[List[int]]:
    for ind in range(len(chromosomes)):
        for j in range(len(chromosomes[ind])):
            if np.random.randint(low=1, high=100) == MAGIC_NUMBER:
                chromosomes[ind][j] = (chromosomes[ind][j] + 1) % 2

    return chromosomes


def evolve(capacity: int, weights: List[int], costs: List[int], chroms_size: int = 100, epochs: int = 1) \
        -> Tuple[List[int], int]:
    weights, costs = np.array(weights), np.array(costs)
    items_size = len(costs)

    chromosomes = [[np.random.randint(low=0, high=2)
                    for _ in range(items_size)] for _ in range(chroms_size)]

    fitness_results = []
    for idx_chrom in range(chroms_size):
        fitness_results.append((idx_chrom, fitness_function(chromosomes[idx_chrom], capacity, weights, costs)))

    best_ans = (0, fitness_results, chromosomes)
    selected_chroms = selection_function(chromosomes, fitness_results)
    new_chroms = crossover_function(selected_chroms)

    for iteration in range(epochs):
        new_fitness_results = []
        for idx_chrom in range(len(new_chroms)):
            new_fitness_results.append((idx_chrom, fitness_function(new_chroms[idx_chrom], capacity, weights, costs)))

        if new_fitness_results[0][1] > best_ans[1][0][1]:
            best_ans = (iteration, new_fitness_results, new_chroms)

        selected_chroms = selection_function(chromosomes, fitness_results)
        new_chroms = crossover_function(selected_chroms)

    return best_ans[2][best_ans[1][0][0]], best_ans[1][0][1]


def knapsack_benchmark(iters: int = 150) -> None:
    """
    _c.txt - the knapsack capacity.
    _w.txt - the weights of the objects.
    _p.txt - the profits of each object.
    _s.txt - the optimal selection of weights.
    """
    print("Задача о рюкзаке")

    table = []
    headers = ["Среднее время работы", "Стоимость лучшего", "Набор элементов", "Исходное решение"]

    for i in range(1, 8):
        name = f'p0{i}'
        with open(f'{KNAPSACK_BENCHMARKS_PATH}/{name}_c.txt', 'r', encoding='utf8') as text_file:
            capacity = int(text_file.read())

        with open(f'{KNAPSACK_BENCHMARKS_PATH}/{name}_w.txt', 'r', encoding='utf8') as pattern_file:
            weights = pattern_file.read()
            weights = list(map(int, weights.split()))

        with open(f'{KNAPSACK_BENCHMARKS_PATH}/{name}_p.txt', 'r', encoding='utf8') as pattern_file:
            cost = pattern_file.read()
            cost = list(map(int, cost.split()))

        with open(f'{KNAPSACK_BENCHMARKS_PATH}/{name}_s.txt', 'r', encoding='utf8') as pattern_file:
            optimal = pattern_file.read()
            optimal = list(map(int, optimal.split()))

        time_sum = 0
        chroms_size = 100

        for _ in range(iters):
            start_time = time.monotonic()
            final_chroms, knapsack_result = evolve(capacity, weights, cost, chroms_size)
            end_time = time.monotonic()
            time_sum += end_time - start_time
        mean_time = time_sum / iters

        row = [f"{name:<5}{mean_time:.6f}", knapsack_result, final_chroms, optimal]
        table.append(row)

    print(tabulate(table, headers=headers, tablefmt="grid"))


knapsack_benchmark()
