pub struct Sieve(Vec<u32>);

impl Sieve {
    pub fn new(max_value : u32) -> Sieve {
        let mut sieve: Vec<u32> = (0..max_value+1).collect();
        for p in 2..max_value+1 {
            if sieve[p as usize] != p {
                continue
            }
            // Use step_by once stable.
            let mut q = p;
            while q <= max_value {
                sieve[q as usize] = p;
                q += p;
            }
        }
        Sieve(sieve)
    }

    pub fn is_prime(&self, p : u32) -> bool {
        if p <= 1 {
            false
        }
        else {
            (&self.0)[p as usize] == p
        }
    }

    pub fn pd(&self, n : u32) -> Vec<(u32, u32)> {
        let mut pqs = Vec::new();
        let mut n = n;
        while n != 1 {
            let p = (&self.0)[n as usize];
            let mut q = 0;
            while n % p == 0 {
                n /= p;
                q += 1;
            }
            pqs.push((p, q));
        }
        pqs
    }
}

fn main() {
    let sieve = Sieve::new(100);
    for n in 1..40 {
        print!("{}: ", n);
        for (p, q) in sieve.pd(n) {
            print!("{}^{} ", p, q);
        }
        println!("");
    }
}
