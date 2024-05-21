from pathlib import Path
import tsplib95

PROJECT_ROOT = Path(__file__).parent.parent
PROBLEM_FOLDER = PROJECT_ROOT / "data/tsp/"
OPT_TOUR_FOLDER = PROJECT_ROOT / "data/tsp.opt/"

PRBOLEMS = ["a280", "att48", "bays29", "ch150"]

for problem_filename in PRBOLEMS:
    problem = tsplib95.load(str(PROBLEM_FOLDER / f"{problem_filename}.tsp"))
    solution = tsplib95.load(str(OPT_TOUR_FOLDER / f"{problem_filename}.opt.tour"))

    print(
        f"Problem: {problem_filename}, BestFitness: {problem.trace_tours(solution.tours)}"
    )
    print(solution.tours)
