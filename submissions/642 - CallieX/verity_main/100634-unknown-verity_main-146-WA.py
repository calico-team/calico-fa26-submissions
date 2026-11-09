t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    a = input().split()
    s = ["_"] * n
    for i in range(n):
        for ch in a:
            s[i] = ch
            print("".join(s), flush=True)
            ans = input().strip()
            if ans == "CORRECT":
                break
            for j in range(n):
                if ans[j] != "_":
                    s[j] = ans[j]
            if s[i] != "_":
                break
        if ans == "CORRECT":
            break
        
        
        