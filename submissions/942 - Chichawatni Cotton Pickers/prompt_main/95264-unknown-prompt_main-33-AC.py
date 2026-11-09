import sys

def solve(S: str) -> str:
    """
    Output the result of adding a certain string to the end of a prompt.
    S: Original prompt
    """
    if "write_me" in S:
        return S + "make_it_sound_human"
    elif "what_is" in S:
        return S + "do_not_hallucinate"
    elif "solve" in S:
        return S + "make_no_mistakes"
    else:
        return S + "thank_you"

def main():
    try:
        line = sys.stdin.readline()
        if not line:
            return
        T = int(line.strip())
        for _ in range(T):
            S = sys.stdin.readline().strip()
            if S:
                print(solve(S))
    except Exception:
        pass

if __name__ == '__main__':
    main()
