#![feature(i128_type)]
use std::collections::HashMap;

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

// Adapted from Lucy's code for ProjectEuler 10.
pub fn sum_prime(n : i128) -> i128 {
    let r = (n as f64).sqrt() as i128;
    let mut vs = Vec::new();
    for i in 1i128..(r+1) {
        vs.push(n / i);
    }
    for v in (0i128..*vs.last().unwrap()).rev() {
        vs.push(v);
    }
    let mut ss: HashMap<i128, i128> = HashMap::new();
    for v in &vs {
        ss.insert(*v, v*(v+1)/2-1);
    }
    for p in 2..r+1 {
        let sp = ss[&(p-1)];
        if ss[&p] > sp {
            let p2 = p * p;
            for v in &vs {
                if *v < p2 {
                    break;
                }
                let s_v = ss[v] - p*(ss[&(v/p)] - sp);
                ss.insert(*v, s_v);
            }
        }
    }
    ss[&n]
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
    println!("{}", sum_prime(1000000000));
}
