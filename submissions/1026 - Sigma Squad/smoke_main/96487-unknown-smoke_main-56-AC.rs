use std::io::{self, BufWriter, Read, Write};

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut iter = input.split_whitespace();

    let t: usize = match iter.next() {
        Some(s) => s.parse().unwrap(),
        None => return,
    };

    let out = io::stdout();
    let mut writer = BufWriter::new(out.lock());

    for _ in 0..t {
        let n: usize = iter.next().unwrap().parse().unwrap();
        let r: i64 = iter.next().unwrap().parse().unwrap();

        let mut charges = 2;
        let mut next_recharge = 0i64;
        let mut ok = true;

        for _ in 0..n {
            let a: i64 = iter.next().unwrap().parse().unwrap();
            if ok {
                while charges < 2 && a >= next_recharge {
                    charges += 1;
                    next_recharge += r;
                }
                if charges == 0 {
                    ok = false;
                } else {
                    if charges == 2 {
                        next_recharge = a + r;
                    }
                    charges -= 1;
                }
            }
        }

        if ok {
            writeln!(writer, "YES").unwrap();
        } else {
            writeln!(writer, "NO").unwrap();
        }
    }
}
