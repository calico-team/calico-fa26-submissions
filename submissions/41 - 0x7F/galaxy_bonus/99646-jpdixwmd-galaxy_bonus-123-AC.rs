use std::io::stdin;
use crate::Tile::{Blue, Normal, Red, Wall};

#[derive(Debug, Copy, Clone, Eq, PartialEq)]
enum Tile {
    Wall,
    Red,
    Blue,
    Normal
}

impl Tile {
    fn ok(self, other: Self) -> bool {
        match self {
            Wall => false,
            Red => other == Red || other == Normal,
            Blue => other == Blue || other == Normal,
            Normal => other != Wall,
        }
    }
}

#[derive(Debug, Clone)]
struct Dsu {
    vec: Vec<usize>,
}

impl Dsu {
    fn new(size: usize) -> Self {
        Dsu {
            vec: (0..size).collect(),
        }
    }

    #[track_caller]
    fn find(&mut self, x: usize) -> usize {
        if self.vec[x] == x {
            x
        } else {
            self.vec[x] = self.find(self.vec[x]);
            self.vec[x]
        }
    }

    #[track_caller]
    fn merge(&mut self, x: usize, y: usize) {
        let x = self.find(x);
        let y = self.find(y);

        if x != y {
            self.vec[y] = x;
        }
    }

    #[inline]
    fn same(&mut self, x: usize, y: usize) -> bool {
        self.find(x) == self.find(y)
    }
}


impl From<char> for Tile {
    fn from(c: char) -> Self {
        match c {
            'R' => Red,
            'B' => Blue,
            '.' => Normal,
            _ => Wall
        }
    }
}

fn main() {
    let mut stdin = stdin().lines();
    let case_cnt = stdin.next().unwrap().unwrap().parse::<usize>().unwrap();
    for _ in 0..case_cnt {
        let (n, m, q) = {
            let line = stdin.next().unwrap().unwrap();
            let mut iter = line.split_whitespace().map(|s| s.parse::<usize>().unwrap());
            (iter.next().unwrap(), iter.next().unwrap(), iter.next().unwrap())
        };
        let mut grid = vec![vec![Wall; m+2]; n+2];
        for x in 1..=n {
            let line = stdin.next().unwrap().unwrap();
            for (c, y) in line.chars().zip(1..) {
                grid[x][y] = Tile::from(c);
            }
        }
        let mut dsu = Dsu::new(n * m + 2);
        for x in 1..=n {
            for y in 1..=m {
                if Tile::ok(grid[x][y], grid[x-1][y]) {
                    dsu.merge(pos_to_index(x, y, (n, m)), pos_to_index(x-1, y, (n, m)));
                }
                if Tile::ok(grid[x][y], grid[x+1][y]) {
                    dsu.merge(pos_to_index(x, y, (n, m)), pos_to_index(x+1, y, (n, m)));
                }
                if Tile::ok(grid[x][y], grid[x][y-1]) {
                    dsu.merge(pos_to_index(x, y, (n, m)), pos_to_index(x, y-1, (n, m)));
                }
                if Tile::ok(grid[x][y], grid[x][y+1]) {
                    dsu.merge(pos_to_index(x, y, (n, m)), pos_to_index(x, y+1, (n, m)));
                }
            }
        }
        for _ in 0..q {
            let (x1, y1, x2, y2) = {
                let line = stdin.next().unwrap().unwrap();
                let mut iter = line.split_whitespace().map(|s| s.parse::<usize>().unwrap());
                (iter.next().unwrap() + 1, iter.next().unwrap() + 1, iter.next().unwrap() + 1, iter.next().unwrap() + 1)
            };
            if dsu.same(pos_to_index(x1, y1, (n, m)), pos_to_index(x2, y2, (n, m))) {
                println!("YES");
            } else {
                println!("NO");
            }
        }
    }
}

fn pos_to_index(x: usize, y: usize, (n, _): (usize, usize)) -> usize {
    (x - 1) + (y - 1) * n
}