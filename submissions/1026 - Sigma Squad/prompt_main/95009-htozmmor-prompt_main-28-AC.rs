use std::io::{self, Read};

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut iter = input.split_whitespace();

    if let Some(t_str) = iter.next() {
        let t: usize = t_str.parse().unwrap();
        for _ in 0..t {
            if let Some(s) = iter.next() {
                let suffix = if s.contains("write_me") {
                    "make_it_sound_human"
                } else if s.contains("what_is") {
                    "do_not_hallucinate"
                } else if s.contains("solve") {
                    "make_no_mistakes"
                } else {
                    "thank_you"
                };
                println!("{}{}", s, suffix);
            }
        }
    }
}
