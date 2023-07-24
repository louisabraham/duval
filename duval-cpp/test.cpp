#include <chrono>
#include <iostream>
#include <random>
#include "duval.hpp"

string generate_random_string(size_t length, unsigned int seed)
{
    const string characters = "ACGT";
    mt19937 generator(seed);
    uniform_int_distribution<> distribution(0, characters.size() - 1);

    string random_string;
    for (size_t i = 0; i < length; ++i)
    {
        random_string += characters[distribution(generator)];
    }

    return random_string;
}

// naive implementation of min_rotation
int min_rotation_naive(string s)
{
    int n = s.size();
    int imin = 0;
    string smin = s;
    for (int i = 1; i < n; i++)
    {
        rotate(s.begin(), s.begin() + 1, s.end());
        if (s < smin)
        {
            smin = s;
            imin = i;
        }
    }
    return imin;
}

int main()
{
    // correctness
    {
        int N_TESTS = 1000000;
        for (auto N : {1, 2, 3, 4, 5, 10})
            for (int test = 0; test < N_TESTS; test++)
            {
                string s = generate_random_string(N, test);
                if (min_rotation(s) != min_rotation_naive(s))
                {
                    cout << "Error" << endl;
                    return 0;
                }
            }
        cout << "Correctness test passed" << endl;
    }
    // performance
    {
        int N_TESTS = 10000;
        int N = 10000;
        vector<string> strings(N_TESTS);
        vector<int> res(N_TESTS);
        for (int test = 0; test < N_TESTS / 2; test++)
            strings[test] = generate_random_string(N, test);
        for (int test = N_TESTS / 2; test < N_TESTS; test++)
            strings[test] = string(N, 'A');
        auto start = chrono::high_resolution_clock::now();

        long long sum = 0;
        for (int test = 0; test < N_TESTS; test++)
            sum += min_rotation(strings[test]);

        auto end = std::chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end - start;
        std::cerr << "Time: " << diff.count() << " s\n";
        assert(sum != 0);
    }
    return 0;
}