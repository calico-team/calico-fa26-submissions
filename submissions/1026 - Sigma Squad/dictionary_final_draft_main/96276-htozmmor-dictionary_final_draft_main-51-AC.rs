use std::io::{self, Read, Write};

const BITS: u32 = 30;
const EXIT: u32 = 1 << 31;

struct Trie {
    ch: Vec<[u32; 2]>,
    cnt: Vec<u32>,
}

impl Trie {
    fn new() -> Self {
        let mut t = Trie { ch: Vec::new(), cnt: Vec::new() };
        t.reset();
        t
    }

    fn reset(&mut self) {
        self.ch.clear();
        self.cnt.clear();
        self.ch.push([0, 0]);
        self.cnt.push(0);
    }

    fn insert(&mut self, v: u32) {
        let mut cur = 0usize;
        self.cnt[0] += 1;
        for b in (0..BITS).rev() {
            let bit = ((v >> b) & 1) as usize;
            if self.ch[cur][bit] == 0 {
                self.ch.push([0, 0]);
                self.cnt.push(0);
                let id = (self.ch.len() - 1) as u32;
                self.ch[cur][bit] = id;
            }
            cur = self.ch[cur][bit] as usize;
            self.cnt[cur] += 1;
        }
    }

    fn remove(&mut self, v: u32) {
        let mut cur = 0usize;
        self.cnt[0] -= 1;
        for b in (0..BITS).rev() {
            let bit = ((v >> b) & 1) as usize;
            cur = self.ch[cur][bit] as usize;
            self.cnt[cur] -= 1;
        }
    }

    fn max_xor(&self, x: u32) -> u32 {
        let mut cur = 0usize;
        let mut res = 0u32;
        for b in (0..BITS).rev() {
            let want = (((x >> b) & 1) ^ 1) as usize;
            let c = self.ch[cur][want] as usize;
            if c != 0 && self.cnt[c] > 0 {
                res |= 1 << b;
                cur = c;
            } else {
                cur = self.ch[cur][want ^ 1] as usize;
            }
        }
        res
    }
}

fn solve(n: usize, a: &[usize], v: &[u32], trie: &mut Trie) -> Vec<u32> {
    let mut state = vec![0u8; n];
    let mut on_cycle = vec![false; n];
    let mut cyc_nodes: Vec<usize> = Vec::new();
    let mut cyc_start: Vec<usize> = Vec::new();
    let mut path: Vec<usize> = Vec::new();

    for i in 0..n {
        if state[i] != 0 {
            continue;
        }
        let mut x = i;
        while state[x] == 0 {
            state[x] = 1;
            path.push(x);
            x = a[x];
        }
        if state[x] == 1 {
            cyc_start.push(cyc_nodes.len());
            let mut y = x;
            loop {
                on_cycle[y] = true;
                cyc_nodes.push(y);
                y = a[y];
                if y == x {
                    break;
                }
            }
        }
        for &p in &path {
            state[p] = 2;
        }
        path.clear();
    }
    cyc_start.push(cyc_nodes.len());

    let mut head = vec![0usize; n + 1];
    for x in 0..n {
        if !on_cycle[x] {
            head[a[x] + 1] += 1;
        }
    }
    for i in 0..n {
        head[i + 1] += head[i];
    }
    let mut pos = head.clone();
    let mut kids = vec![0u32; head[n]];
    for x in 0..n {
        if !on_cycle[x] {
            kids[pos[a[x]]] = x as u32;
            pos[a[x]] += 1;
        }
    }

    let mut f = vec![0u32; n];
    let mut ans = vec![0u32; n];
    let mut stack: Vec<u32> = Vec::new();

    for k in 0..cyc_start.len() - 1 {
        let cyc = &cyc_nodes[cyc_start[k]..cyc_start[k + 1]];
        trie.reset();

        let mut e = 0u32;
        for &c in cyc {
            f[c] = e;
            e ^= v[c];
        }
        let total = e;
        for &c in cyc {
            trie.insert(f[c]);
            trie.insert(f[c] ^ total);
        }
        for &c in cyc {
            ans[c] = trie.max_xor(f[c]);
        }

        for &c in cyc {
            stack.extend_from_slice(&kids[head[c]..head[c + 1]]);
            while let Some(top) = stack.pop() {
                if top & EXIT != 0 {
                    trie.remove(f[(top ^ EXIT) as usize]);
                    continue;
                }
                let x = top as usize;
                f[x] = v[x] ^ f[a[x]];
                ans[x] = trie.max_xor(f[x]);
                if head[x] < head[x + 1] {
                    trie.insert(f[x]);
                    stack.push(top | EXIT);
                    stack.extend_from_slice(&kids[head[x]..head[x + 1]]);
                }
            }
        }
    }

    ans
}

struct Scanner {
    buf: Vec<u8>,
    pos: usize,
}

impl Scanner {
    fn next(&mut self) -> u64 {
        while self.pos < self.buf.len() && !self.buf[self.pos].is_ascii_digit() {
            self.pos += 1;
        }
        let mut r = 0u64;
        while self.pos < self.buf.len() && self.buf[self.pos].is_ascii_digit() {
            r = r * 10 + (self.buf[self.pos] - b'0') as u64;
            self.pos += 1;
        }
        r
    }
}

fn main() {
    let mut buf = Vec::new();
    io::stdin().read_to_end(&mut buf).unwrap();
    let mut sc = Scanner { buf, pos: 0 };

    let t = sc.next() as usize;
    let mut out: Vec<u8> = Vec::with_capacity(1 << 22);
    let mut trie = Trie::new();

    for _ in 0..t {
        let n = sc.next() as usize;
        let a: Vec<usize> = (0..n).map(|_| sc.next() as usize - 1).collect();
        let v: Vec<u32> = (0..n).map(|_| sc.next() as u32).collect();

        let ans = solve(n, &a, &v, &mut trie);
        for (i, x) in ans.iter().enumerate() {
            if i > 0 {
                out.push(b' ');
            }
            write!(out, "{}", x).unwrap();
        }
        out.push(b'\n');
    }

    io::stdout().write_all(&out).unwrap();
}
