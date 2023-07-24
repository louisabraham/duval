#include <string>
#include <vector>
using namespace std;

// https://cp-algorithms.com/string/lyndon_factorization.html
vector<string> duval(string const &s)
{
    int n = s.size();
    int i = 0;
    vector<string> factorization;
    while (i < n)
    {
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j])
        {
            if (s[k] < s[j])
                k = i;
            else
                k++;
            j++;
        }
        while (i <= k)
        {
            factorization.push_back(s.substr(i, j - k));
            i += j - k;
        }
    }
    return factorization;
}

int min_rotation(string s)
{
    int a = 0, N = (int)s.size();
    s += s; // always faster than using modulo for b+1
    for (int b = 0; b < N; ++b)
    {
        for (int i = 0; a + i < N; ++i)
        {
            auto sai = s[a + i], sbi = s[b + i];
            if (a + i == b || sai < sbi)
            {
                if (i > 1)
                    b += i - 1;
                break;
            }
            if (sai > sbi)
            {
                a = b;
                break;
            }
        }
    }
    return a;
}
