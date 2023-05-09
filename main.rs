#[derive(Copy, Clone)]
struct Element {
    calc: bool,
    r: f64,
}

const CONST_FACT: [f64; 5] = [-25.0, -233.0, -995.0, -1866.0, -1080.0];
fn suite(a: u32, cache: &mut [Element; 100]) -> f64 {
    if cache[a as usize].calc {
        cache[a as usize].r
    } else {
        let mut r = 0.0;
        for i in 0..5 {
            let index = a - i - 1;
            let mut n;
            if cache[index as usize].calc {
                n = cache[index as usize].r;
            } else {
                n = suite(index, cache);
            }
            n *= CONST_FACT[i as usize];
            r += n;
        }
        cache[a as usize].calc = true;
        cache[a as usize].r = r;
        r
    }
}

//Main function in rust
fn main() {
    let mut cache: [Element; 100] = [Element {
        calc: false,
        r: 0.0,
    }; 100];

    const CONST_DEP: [f64; 5] = [-1.0, 28.0, -240.0, 1948.0, -16080.0];
    for i in 0..5 {
        cache[i].calc = true;
        cache[i].r = CONST_DEP[i];
    }

    let a = 80;
    let mut r = 0.0;
    const NB_TESTS: u64 = 50;
    let mut total = 0.0; // in µs
    for _ in 0..NB_TESTS {
        use std::time::Instant;
        let now = Instant::now();
        r = suite(a, &mut cache);
        let elapsed = now.elapsed();
        total += ((elapsed.as_secs() as f64) * 1e6 + elapsed.subsec_nanos() as f64 / 1e3);
    }

    total = total / (NB_TESTS as f64);

    println!("a({}) = {:.4e}", a, r);
    println!("Elapsed time: {} µs", total);
}
