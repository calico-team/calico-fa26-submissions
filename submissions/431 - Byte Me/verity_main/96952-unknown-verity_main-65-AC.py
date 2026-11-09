T = int(input())

for i in range(T):
    N, K = map(int, input().split())
    A= input().split()
    ans = ["?"] * N
    for letter in A:
        inte = ""
        for i in range(N):
            if ans[i] == "?":
                inte += letter
            else:
                inte += ans[i]
        print(inte, flush=True)
        result = input().strip()
        if result == "CORRECT":
            break
        for i in range(N):
            if result[i] != "_":
                ans[i] = result[i]
    else:
        inte = "".join(ans)
        print(inte,flush=True)
        result = input().strip()