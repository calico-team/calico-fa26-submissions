use std::io::stdin;

fn main() {
    let mut stdin = stdin().lines();
    let case_cnt: usize = stdin.next().unwrap().unwrap().parse().unwrap();
    for _ in 0..case_cnt {
        let string = stdin.next().unwrap().unwrap();
        if string.contains("write_me") {
            println!("{string}make_it_sound_human")
        } else if string.contains("what_is") {
            println!("{string}do_not_hallucinate")
        } else if string.contains("solve") {
            println!("{string}make_no_mistakes")
        } else {
            println!("{string}thank_you")
        }
    }
}