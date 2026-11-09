t = int(input())

for _ in range(t):
    n, k = map(int, input().split())
    a = input().split()
    s = ["_"] * n
    for ch in a:
        guess = ""
        for i in range(n):
            if s[i] == "_":
                guess += ch
            else:
                guess += s[i]
        print(guess, flush=True)
        ans = input().strip()
        if ans == "CORRECT":
            break
        for i in range(n):
            if ans[i] != "_":
                s[i] = ans[i]
                