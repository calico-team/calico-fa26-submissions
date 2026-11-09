t = int(input())
for T in range(t):
    s = input().split()
    n = int(s[0])
    k = int(s[1])
    s = input().split()
    a = []
    for i in range(k):a.append(s[i])
    seq = [-1] * n
    res = "_"*n
    while res != "CORRECT":
        ans = ""
        for i in range(n):
            if res[i] == "_":
                seq[i] += 1
            ans += a[seq[i]]

        print(ans)
        res = input()




