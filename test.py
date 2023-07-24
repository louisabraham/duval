import random
from time import time

from duval import min_rotation
from duval_pure import min_rotation as min_rotation_pure


def random_string(n, seed):
    random.seed(seed)
    return "".join(random.choice("ACGT") for _ in range(n))


N_TESTS = 10000
N = 10

for seed in range(N_TESTS):
    s = random_string(N, seed)
    assert min_rotation(s) == min_rotation_pure(s)


N_TESTS = 500
N = 10000

strings = [random_string(N, seed) for seed in range(N_TESTS)] + [
    "A" * N for _ in range(N_TESTS)
]

start = time()
ans = [min_rotation(s) for s in strings]
end = time()
cpp = end - start
print("C++ time:", cpp)

start = time()
ans1 = [min_rotation_pure(s) for s in strings]
end = time()
python = end - start
print("Python time:", python)

assert ans == ans1
print("Speedup:", python / cpp)
