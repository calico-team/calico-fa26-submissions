t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    chars = input().split()
    known = ["_"] * n
    for i in range(k):
        guess = ""
        for ch in known:
            if ch == "_":
                guess += chars[i]
            else:
                guess += ch
        print(guess, flush=True)
        resp = input().strip()
        if resp == "CORRECT":
            break
        for j in range(n):
            if resp[j] != "_":
                known[j] = resp[j]
