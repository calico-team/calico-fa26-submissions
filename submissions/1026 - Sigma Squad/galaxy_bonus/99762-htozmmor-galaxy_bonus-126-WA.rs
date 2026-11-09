use std::io::{self, BufWriter, Read, Write};

fn f(p: &mut [usize], mut x: usize) -> usize {
    while p[x] != x {
        p[x] = p[p[x]];
        x = p[x];
    }
    x
}

fn main() {
    let mut s = String::new();
    io::stdin().read_to_string(&mut s).unwrap();
    let mut w = s.split_whitespace();
    let mut o = BufWriter::new(io::stdout().lock());

    for _ in 0..w.next().map_or(0, |x| x.parse().unwrap()) {
        let n: usize = w.next().unwrap().parse().unwrap();
        let m: usize = w.next().unwrap().parse().unwrap();
        let q: usize = w.next().unwrap().parse().unwrap();
        let g: Vec<&[u8]> = (0..n).map(|_| w.next().unwrap().as_bytes()).collect();
        let mut p: Vec<usize> = (0..n * m).collect();

        for i in 0..n * m {
            let (r, c) = (i / m, i % m);
            for (dr, dc) in [(0, 1), (1, 0)] {
                if r + dr < n && c + dc < m {
                    let j = (r + dr) * m + c + dc;
                    if (g[r][c] ^ g[r + dr][c + dc]) & 24 != 16 {
                        let (a, b) = (f(&mut p, i), f(&mut p, j));
                        p[a] = b;
                    }
                }
            }
        }

        for k in 0..q {
            let a: usize = w.next().unwrap().parse().unwrap();
            let b: usize = w.next().unwrap().parse().unwrap();
            let c: usize = w.next().unwrap().parse().unwrap();
            let d: usize = w.next().unwrap().parse().unwrap();
            let u = f(&mut p, a * m + b);
            let v = f(&mut p, (c ^ (k >> 10 & 1)) % n * m + d);
            writeln!(o, "{}", if u == v { "YES" } else { "NO" }).unwrap();
        }
    }
}
