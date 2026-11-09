use std::io::{stdin, Lines, StdinLock};

fn main() {
    let mut stdin = stdin().lines();
    let case_cnt = stdin.next().unwrap().unwrap().parse::<usize>().unwrap();
    'cases: for _ in 0..case_cnt {
        let (len, type_cnt) = {
            let line = stdin.next().unwrap().unwrap();
            let mut iter = line.split_whitespace().map(|s| s.parse::<usize>().unwrap());
            (iter.next().unwrap(), iter.next().unwrap())
        };
        let characters = stdin.next().unwrap().unwrap().split_whitespace().map(|s| s.parse::<char>().unwrap()).collect::<Vec<_>>();
        eprintln!("{characters:?}");
        let mut guess = vec![characters[0]; len];
        for &c in &characters[1..] {
            eprintln!("Test 01: {c}, {guess:?}");
            submit(&guess);
            let res = match response(&mut stdin) {
                Ok(_) => continue 'cases,
                Err(e) => e,
            };
            for (i, a) in res.iter().enumerate() {
                if a.is_none() {
                    guess[i] = c;
                }
            }
        }
        submit(&guess);
        response(&mut stdin).unwrap()
    }
}

fn submit(guess: &[char]) {
    for c in guess {
        print!("{c}");
    }
    println!();
}

fn response(stdin: &mut Lines<StdinLock>) -> Result<(), Vec<Option<char>>> {
    let line = stdin.next().unwrap().unwrap();
    if line.trim() == "CORRECT" {
        return Ok(());
    }
    Err(line.trim().chars().map(|c| if c == '_' { None } else { Some(c) }).collect())
}