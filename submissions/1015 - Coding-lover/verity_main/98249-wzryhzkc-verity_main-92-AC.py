t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    a = input().split()
    ans = ["_"] * n
    done = False
    for ch in a:
        guess = ch * n
        print(guess, flush=True)
        resp = input().strip()
        if resp == "CORRECT":
            done = True
            break
        i = 0
        while i < n:
            if resp[i] != "_":
                ans[i] = resp[i]
            i = i + 1
        if "_" not in ans:
            break
    if not done:
        guess = "".join(ans)
        print(guess, flush=True)
        resp = input().strip()
