def solve(S: str) -> str:

    if "write_me" in S:
        S+="make_it_sound_human"
    elif "what_is" in S:
        S+="do_not_hallucinate"
    elif "solve" in S:
        S+="make_no_mistakes"
    else:
        S+="thank_you"
    return S

def main():
    T=0
    T = int(input())
    #if T>=1 and T<=100:
    for _ in range(T):
        S = input()
        print(solve(S))

if __name__ == "__main__":
    main()