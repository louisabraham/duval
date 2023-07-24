pub fn duval(s: &str) -> Vec<String> {
    let n: usize = s.len();
    let mut i: usize = 0;
    let mut factorization: Vec<String> = Vec::new();
    while i < n {
        let mut j: usize = i + 1;
        let mut k: usize = i;
        while j < n && s.as_bytes()[k] <= s.as_bytes()[j] {
            if s.as_bytes()[k] < s.as_bytes()[j] {
                k = i;
            } else {
                k += 1;
            }
            j += 1;
        }
        while i <= k {
            factorization.push(s[i..j].to_string());
            i += j - k;
        }
    }
    factorization
}

pub fn min_rotation(s: &[u8]) -> usize {
    let mut a: usize = 0;
    let n: usize = s.len();
    let mut b: usize = 0;
    while b < n {
        let mut i: usize = 0;
        while a + i < n {
            let sai: u8 = s[a + i];
            let sbi: u8 = s[if b + i < n { b + i } else { b + i - n }];
            if a + i == b || sai < sbi {
                if i > 1 {
                    b += i - 1;
                }
                break;
            }
            if sai > sbi {
                a = b;
                break;
            }
            i += 1;
        }
        b += 1;
    }
    a
}

#[cfg(test)]
mod tests {
    use super::*;
    use rand::Rng;
    use rand::SeedableRng;

    fn generate_random_string(length: usize, seed: u64) -> Vec<u8> {
        const CHARACTERS: &[u8] = b"ACGT";
        let mut rng: rand::rngs::StdRng = rand::rngs::StdRng::seed_from_u64(seed);

        (0..length)
            .map(|_| {
                let idx: usize = rng.gen_range(0..CHARACTERS.len());
                CHARACTERS[idx]
            })
            .collect()
    }

    fn min_rotation_naive(s: &[u8]) -> usize {
        let n: usize = s.len();
        let mut smin: Vec<u8> = s.to_vec();
        let mut s_clone: Vec<u8> = s.to_vec();
        let mut imin: usize = 0;
        for i in 1..n {
            s_clone.rotate_left(1);
            if s_clone < smin {
                smin = s_clone.clone();
                imin = i;
            }
        }
        imin
    }

    #[test]
    fn test_min_rotation() {
        const N_TESTS: u32 = 100000;
        const N: usize = 10;

        for test in 0..N_TESTS {
            let s: Vec<u8> = generate_random_string(N, test as u64);
            assert_eq!(min_rotation(&s), min_rotation_naive(&s));
        }
    }

    #[test]
    fn test_min_rotation_large() {
        const N_TESTS: u32 = 10000;
        const N: usize = 10000;

        let mut strings: Vec<Vec<u8>> = vec![vec![b'A'; N]; N_TESTS as usize];
        for test in 0..N_TESTS / 2 {
            strings[test as usize] = generate_random_string(N, test as u64);
        }

        let mut sum = 0;
        let start = std::time::Instant::now();
        for s in strings {
            sum += min_rotation(&s);
        }
        let duration = start.elapsed();
        // assert sum != 0 to avoid compiler optimizations
        assert_ne!(sum, 0);
        println!("Time: {:?}", duration);
    }
}
