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
