T = int(input())
for _ in range(T):
    n, k = map(int, input().split())
    letters = input().split()
    known = ["_"] * n
    # put the same letter in every spot we dont know yet, judge tells us where it was right
    for ch in letters:
        guess = "".join(ch if known[i] == "_" else known[i] for i in range(n))
        print(guess, flush=True)
        res = input().strip()
        if res == "CORRECT":
            break
        for i in range(n):
            if res[i] != "_":
                known[i] = res[i]
