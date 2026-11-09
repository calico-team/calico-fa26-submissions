use std::io::{self, BufWriter, Read, Write};

#[derive(Clone, Copy)]
struct TrieNode {
    child: [u32; 2],
    cnt: i32,
}

struct Trie {
    nodes: Vec<TrieNode>,
}

impl Trie {
    fn new(capacity: usize) -> Self {
        let mut nodes = Vec::with_capacity(capacity);
        nodes.push(TrieNode {
            child: [0, 0],
            cnt: 0,
        });
        Self { nodes }
    }

    fn clear(&mut self) {
        self.nodes.truncate(1);
        self.nodes[0] = TrieNode {
            child: [0, 0],
            cnt: 0,
        };
    }

    fn update(&mut self, val: u32, delta: i32) {
        let mut u = 0usize;
        self.nodes[u].cnt += delta;
        for b in (0..30).rev() {
            let bit = ((val >> b) & 1) as usize;
            let mut nxt = self.nodes[u].child[bit] as usize;
            if nxt == 0 {
                nxt = self.nodes.len();
                self.nodes.push(TrieNode {
                    child: [0, 0],
                    cnt: 0,
                });
                self.nodes[u].child[bit] = nxt as u32;
            }
            u = nxt;
            self.nodes[u].cnt += delta;
        }
    }

    fn query(&self, val: u32) -> u32 {
        let mut u = 0usize;
        let mut res = 0u32;
        for b in (0..30).rev() {
            let bit = ((val >> b) & 1) as usize;
            let want = bit ^ 1;
            let nxt_want = self.nodes[u].child[want] as usize;
            if nxt_want != 0 && self.nodes[nxt_want].cnt > 0 {
                res |= 1 << b;
                u = nxt_want;
            } else {
                u = self.nodes[u].child[bit] as usize;
            }
        }
        res
    }
}

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
    let mut trie = Trie::new(1);

    for _ in 0..t {
        let n: usize = iter.next().unwrap().parse().unwrap();
        let mut nxt = vec![0usize; n];
        let mut in_deg = vec![0u32; n];
        let mut head = vec![u32::MAX; n];
        let mut to = vec![0u32; n];
        let mut next_edge = vec![u32::MAX; n];

        for u in 0..n {
            let a: usize = iter.next().unwrap().parse().unwrap();
            let v = a - 1;
            nxt[u] = v;
            in_deg[v] += 1;
            to[u] = u as u32;
            next_edge[u] = head[v];
            head[v] = u as u32;
        }

        let mut val = vec![0u32; n];
        for u in 0..n {
            val[u] = iter.next().unwrap().parse().unwrap();
        }

        let mut queue = Vec::with_capacity(n);
        let mut on_cycle = vec![true; n];
        for u in 0..n {
            if in_deg[u] == 0 {
                queue.push(u);
            }
        }

        let mut q_idx = 0;
        while q_idx < queue.len() {
            let u = queue[q_idx];
            q_idx += 1;
            on_cycle[u] = false;
            let v = nxt[u];
            in_deg[v] -= 1;
            if in_deg[v] == 0 {
                queue.push(v);
            }
        }

        let mut visited_cycle = vec![false; n];
        let mut d = vec![0u32; n];
        let mut ans = vec![0u32; n];
        let mut cycle = Vec::new();
        let mut b_pref = Vec::new();
        let mut stack = Vec::new();

        for i in 0..n {
            if on_cycle[i] && !visited_cycle[i] {
                cycle.clear();
                let mut curr = i;
                while !visited_cycle[curr] {
                    visited_cycle[curr] = true;
                    cycle.push(curr);
                    curr = nxt[curr];
                }

                let l = cycle.len();
                b_pref.clear();
                b_pref.push(0u32);
                for idx in 0..l {
                    let next_b = b_pref[idx] ^ val[cycle[idx]];
                    b_pref.push(next_b);
                }
                let total_x = b_pref[l];

                trie.clear();
                for idx in 0..l {
                    let u = cycle[idx];
                    d[u] = b_pref[idx];
                    trie.update(b_pref[idx], 1);
                    trie.update(total_x ^ b_pref[idx], 1);
                }

                for &u in &cycle {
                    ans[u] = trie.query(d[u]);
                }

                for &u in &cycle {
                    let mut e = head[u];
                    while e != u32::MAX {
                        let ch = to[e] as usize;
                        if !on_cycle[ch] {
                            stack.push((ch, u, false));
                            while let Some((curr_u, p, exiting)) = stack.pop() {
                                if !exiting {
                                    d[curr_u] = d[p] ^ val[curr_u];
                                    ans[curr_u] = trie.query(d[curr_u]);
                                    trie.update(d[curr_u], 1);
                                    stack.push((curr_u, p, true));
                                    let mut ce = head[curr_u];
                                    while ce != u32::MAX {
                                        let next_ch = to[ce] as usize;
                                        stack.push((next_ch, curr_u, false));
                                        ce = next_edge[ce as usize];
                                    }
                                } else {
                                    trie.update(d[curr_u], -1);
                                }
                            }
                        }
                        e = next_edge[e as usize];
                    }
                }
            }
        }

        for u in 0..n {
            if u > 0 {
                write!(writer, " ").unwrap();
            }
            write!(writer, "{}", ans[u]).unwrap();
        }
        writeln!(writer).unwrap();
    }
}
