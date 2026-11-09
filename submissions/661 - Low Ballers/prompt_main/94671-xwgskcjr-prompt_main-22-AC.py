def solve(S: str) -> None:
    ans = ""
    if "write_me" in S:
        ans = S + "make_it_sound_human"
    elif "what_is" in S:
        ans = S + "do_not_hallucinate"
    elif "solve" in S:
        ans = S + "make_no_mistakes"
    else:
        ans = S + "thank_you"
    print(ans)

def main():
    T = int(input())
    for _ in range(T):
        S = input()
        solve(S)

if __name__ == "__main__":
    main()