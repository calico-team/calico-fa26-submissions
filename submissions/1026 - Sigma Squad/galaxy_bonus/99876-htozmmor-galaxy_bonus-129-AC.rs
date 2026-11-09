use std::io::{self, Read, Write};

fn find(p: &mut Vec<usize>, mut x: usize) -> usize {
    while p[x] != x {
        p[x] = p[p[x]];
        x = p[x];
    }
    x
}

fn unite(p: &mut Vec<usize>, a: usize, b: usize) {
    let ra = find(p, a);
    let rb = find(p, b);
    if ra != rb {
        p[ra] = rb;
    }
}

fn active(t: u8, m: usize) -> bool {
    t == b'.' || (m == 0 && t == b'B') || (m == 1 && t == b'R')
}

fn main() {
    let mut s = String::new();
    io::stdin().read_to_string(&mut s).unwrap();
    let mut it = s.split_ascii_whitespace();
    let t: usize = it.next().unwrap().parse().unwrap();
    let mut out = String::new();
    for _ in 0..t {
        let n: usize = it.next().unwrap().parse().unwrap();
        let m: usize = it.next().unwrap().parse().unwrap();
        let q: usize = it.next().unwrap().parse().unwrap();
        let mut g: Vec<u8> = Vec::with_capacity(n * m);
        for _ in 0..n {
            g.extend_from_slice(it.next().unwrap().as_bytes());
        }
        let mut p: Vec<usize> = (0..2 * n * m).collect();
        for r in 0..n {
            for c in 0..m {
                let u = r * m + c;
                if g[u] == b'.' {
                    unite(&mut p, 2 * u, 2 * u + 1);
                }
                for md in 0..2 {
                    if !active(g[u], md) {
                        continue;
                    }
                    if c + 1 < m && active(g[u + 1], md) {
                        unite(&mut p, 2 * u + md, 2 * (u + 1) + md);
                    }
                    if r + 1 < n && active(g[u + m], md) {
                        unite(&mut p, 2 * u + md, 2 * (u + m) + md);
                    }
                }
            }
        }
        for _ in 0..q {
            let rs: usize = it.next().unwrap().parse().unwrap();
            let cs: usize = it.next().unwrap().parse().unwrap();
            let re: usize = it.next().unwrap().parse().unwrap();
            let ce: usize = it.next().unwrap().parse().unwrap();
            let a = rs * m + cs;
            let b = re * m + ce;
            let root = find(&mut p, 2 * a);
            let mut ok = false;
            for md in 0..2 {
                if active(g[b], md) && find(&mut p, 2 * b + md) == root {
                    ok = true;
                }
            }
            out.push_str(if ok { "YES\n" } else { "NO\n" });
        }
    }
    io::stdout().write_all(out.as_bytes()).unwrap();
}
