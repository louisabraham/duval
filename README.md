# Duval algorithm for Lyndon factorization and smallest rotation computation

We provide implementation of Duval algorithm for Lyndon factorization and smallest rotation computation in C++, Rust and Python.

Our code for the Lyndon factorization is based on [this implementation](https://cp-algorithms.com/string/lyndon_factorization.html)

Our code for the smallest rotation computation is custom and highly optimized (for the C++ and Rust versions).

# Usage

## Pure Python

Just use the following code snippet (from `duval_pure.py`)

```python
def min_rotation(s):
    N = len(s)
    s += s
    a = b = 0
    while b < N:
        for i in range(N - a):
            sai = s[a + i]
            sbi = s[b + i]
            if sai < sbi or a + i == b:
                if i:
                    b += i - 1
                break
            if sai > sbi:
                a = b
                break
        b += 1
    return a
```

## Call C++ from Python
 

Requires pybind11 (`pip install pybind11`).

Install with `pip install .`

```python
from duval import duval, min_rotation

s = "abracadabra"
print(duval(s))
print(min_rotation(s))
```
```

## C++ version

Simply include `duval.hpp`.

```cpp
#include <iostream>
#include <string>
#include "duval.hpp"

int main()
{
    std::string s = "abracadabra";
    for (auto &factor : duval(s))
        std::cout << factor << std::endl;
    std::cout << min_rotation(s) << std::endl;
}
```

## Rust version

Code is provided in `duval-rs`.

# Testing

We provide simple tests for the Python, C++ and Rust versions.

## C++


`g++ --std=c++11 -O3 test.cpp -o test && ./test`

We do extended testing for the C++ version with random strings against a very naive implementation. The random strings are generated with fixed seeds to ensure reproducibility.

We also display the performance. On our laptop, computing `min_rotation` for 10000 strings (half random and half random) of length 10000 takes 0.2s.

## Python

`python test.py`

We test both the pure Python and the C++ version and compare their performance.
The Python version is about 150x slower than the C++ version.

## Rust

`cargo test --release -- --nocapture`

The Rust version has about the same performance as the C++ version.