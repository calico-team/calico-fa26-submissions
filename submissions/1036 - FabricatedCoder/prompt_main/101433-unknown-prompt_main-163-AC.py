def solve(S: str) -> str:
    if "write_me" in S:
        return S + "make_it_sound_human"
    elif "what_is" in S:
        return S + "do_not_hallucinate"
    elif "solve" in S:
        return S + "make_no_mistakes"
    else:
        return S + "thank_you"

def main():
    import sys

    input_data = sys.stdin.read().splitlines()
    if not input_data:
        return

    T = int(input_data[0])
    for i in range(1, T + 1):
        print(solve(input_data[i].strip()))

if __name__ == "__main__":
    main()