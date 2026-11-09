import sys


def solve():
    input_line = sys.stdin.readline()
    if not input_line:
        return
    T = int(input_line.strip())

    for _ in range(T):
        line1 = sys.stdin.readline().split()
        while not line1:
            line1 = sys.stdin.readline().split()
        N = int(line1[0])
        K = int(line1[1])

        allowed_chars = sys.stdin.readline().split()
        while len(allowed_chars) < K:
            allowed_chars.extend(sys.stdin.readline().split())

        known = ["_"] * N
        resp = ""

        for idx, c in enumerate(allowed_chars):
            if "_" not in known:
                break

            if idx == K - 1:
                for i in range(N):
                    if known[i] == "_":
                        known[i] = c
                guess_str = "".join(known)
            else:
                guess_str = c * N

            print(guess_str, flush=True)
            resp = sys.stdin.readline().strip()

            if resp == "CORRECT":
                break

            for i in range(N):
                if resp[i] != "_":
                    known[i] = resp[i]

        if "_" not in known and resp != "CORRECT":
            guess_str = "".join(known)
            print(guess_str, flush=True)
            resp = sys.stdin.readline().strip()


if __name__ == "__main__":
    solve()