use std::cmp::min;
use std::io::stdin;

fn main() {
    let mut stdin = stdin().lines();
    let case_cnt = stdin.next().unwrap().unwrap().parse::<usize>().unwrap();

    'outer: for _ in 0..case_cnt {
        let (request_cnt, recharge_time) = {
            let line = stdin.next().unwrap().unwrap();
            let mut iter = line.split_whitespace().map(|x| x.parse::<usize>().unwrap());
            (iter.next().unwrap(), iter.next().unwrap())
        };

        let requests = stdin.next().unwrap().unwrap().split_whitespace().map(|x| x.parse::<usize>().unwrap()).collect::<Vec<_>>();

        let mut refreshing: Option<usize> = None;
        let mut smoke = recharge_time * 2;

        for request in requests {
            if let Some(t) = refreshing {
                smoke = min(recharge_time * 2, smoke + request - t)
            }
            refreshing = Some(request);
            if smoke >= recharge_time {
                smoke -= recharge_time;
            } else {
                println!("NO");
                continue 'outer;
            }
        }
        println!("YES");
    }
}