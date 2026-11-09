def solve(s: str) -> str:
    if "write_me" in s:
        s+="make_it_sound_human"
    elif "what_is" in s:
        s+="do_not_hallucinate"
    elif "solve" in s:
        s+="make_no_mistakes"
    else:
        s+="thank_you"
    return s

def main():
    T = int(input())
    for _ in range(T):
        S = input()
        print(solve(S))

if __name__ == "__main__":
    main()