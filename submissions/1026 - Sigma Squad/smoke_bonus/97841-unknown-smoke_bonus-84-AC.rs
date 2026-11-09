use std::io::{self, Read};

fn main() {
    let mut s = String::new();
    io::stdin().read_to_string(&mut s).unwrap();
    let mut it = s.split_whitespace().flat_map(str::parse::<i64>);
    for _ in 0..it.next().unwrap_or(0) {
        let (n, r) = (it.next().unwrap(), it.next().unwrap());
        let (_, _, f) = (0..n).fold((2i64, 0i64, 1i64), |(c, d, f), _| {
            let x = it.next().unwrap();
            let y = x ^ (((x >> 17) & 1) * r);
            let k = if y >= d { ((y - d) / r + 1).min(2 - c).max(0) } else { 0 };
            let m = c + k;
            let nf = f & ((m > 0) as i64);
            let nd = if m == 2 { y + r } else { d + k * r };
            ((m - 1).max(0), nd, nf)
        });
        println!("{}", if f != 0 { "YES" } else { "NO" });
    }
}
