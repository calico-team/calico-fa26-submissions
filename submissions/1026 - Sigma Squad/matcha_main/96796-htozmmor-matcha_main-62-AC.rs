use std::io::{self, Read, Write};

fn main() {
    let mut s = String::new();
    io::stdin().read_to_string(&mut s).unwrap();
    let mut it = s.split_ascii_whitespace().map(|x| x.parse::<u64>().unwrap());
    let t = it.next().unwrap() as usize;
    let mut out = String::with_capacity(t * 12);
    let mut ls: Vec<u64> = Vec::new();
    let mut iv: Vec<(u32, u64, u64)> = Vec::new();
    let mut pin: Vec<bool> = Vec::new();
    let mut sg: Vec<u64> = Vec::new();
    for _ in 0..t {
        let n = it.next().unwrap() as usize;
        ls.clear();
        for _ in 0..n {
            ls.push(it.next().unwrap());
        }
        iv.clear();
        let mut d = 0u64;
        for &l in ls.iter() {
            let r = it.next().unwrap();
            if l == r {
                d ^= l;
            } else {
                let h = 63 - (l ^ r).leading_zeros();
                d ^= l | ((1u64 << h) - 1);
                iv.push((h, l, r));
            }
        }
        iv.sort_unstable_by(|a, b| b.0.cmp(&a.0));
        let k = iv.len();
        pin.clear();
        pin.resize(k, false);
        sg.clear();
        sg.resize(k, 0);
        let mut ucnt = [0usize; 30];
        let mut upar = [0u64; 30];
        let mut q = 0u64;
        let mut pre = 0u64;
        let mut res = None;
        let mut ptr = 0usize;
        for c in (0..30u32).rev() {
            let bit = |v: u64| (v >> c) & 1;
            let mut mmax = 0u64;
            let mut gs = 0usize;
            let mut ge = 0usize;
            let mut i = 0usize;
            while i < ptr {
                let h = iv[i].0 as usize;
                let mut j = i;
                let (mut sp, mut su, mut flex, mut par) = (0u64, 0u64, false, 0u64);
                while j < ptr && iv[j].0 as usize == h {
                    let a = bit(iv[j].1) ^ 1;
                    let b = bit(iv[j].2);
                    if pin[j] {
                        sp += if sg[j] == 0 { a } else { b };
                    } else if a == b {
                        flex = true;
                        su += a;
                    } else {
                        su += 1;
                        par ^= b;
                    }
                    j += 1;
                }
                let mut mg = sp;
                if ucnt[h] >= 2 {
                    mg += if flex || par == upar[h] { su } else { su - 1 };
                }
                if mg > 0 {
                    gs = i;
                    ge = j;
                }
                mmax += mg;
                i = j;
            }
            let mut e = ptr;
            while e < k && iv[e].0 == c {
                e += 1;
            }
            let dc = bit(d);
            let full = pre | ((1u64 << (c + 1)) - 1);
            if e > ptr {
                if mmax > 0 {
                    res = Some(full);
                    break;
                }
                let pc = 1 ^ dc ^ q;
                q ^= pc;
                pre |= 1u64 << c;
                if e - ptr == 1 {
                    pin[ptr] = true;
                    sg[ptr] = pc;
                } else {
                    ucnt[c as usize] = e - ptr;
                    upar[c as usize] = pc;
                }
                ptr = e;
            } else {
                let kc = dc ^ q;
                if kc + mmax >= 2 {
                    res = Some(full);
                    break;
                }
                if kc + mmax == 1 {
                    pre |= 1u64 << c;
                    if kc == 0 {
                        let h = iv[gs].0 as usize;
                        if ucnt[h] >= 2 {
                            let (mut sp, mut both, mut cand, mut ci) = (0u64, 0usize, 0usize, 0usize);
                            for j in gs..ge {
                                let a = bit(iv[j].1) ^ 1;
                                let b = bit(iv[j].2);
                                if pin[j] {
                                    sp += if sg[j] == 0 { a } else { b };
                                } else if a == 1 && b == 1 {
                                    both += 1;
                                } else if a != b {
                                    cand += 1;
                                    ci = j;
                                }
                            }
                            if sp == 0 && both == 0 && cand == 1 {
                                let v = bit(iv[ci].2);
                                pin[ci] = true;
                                sg[ci] = v;
                                ucnt[h] -= 1;
                                upar[h] ^= v;
                                if ucnt[h] == 1 {
                                    for j in gs..ge {
                                        if !pin[j] {
                                            pin[j] = true;
                                            sg[j] = upar[h];
                                        }
                                    }
                                    ucnt[h] = 0;
                                    upar[h] = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
        let ans = res.unwrap_or(pre);
        out.push_str(&ans.to_string());
        out.push('\n');
    }
    io::stdout().write_all(out.as_bytes()).unwrap();
}
