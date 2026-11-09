t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    ities = list(input().split())
    curr = [0] * n
    while True:
        printer = []
        for i in curr:
            printer.append(ities[i])
        print("".join(printer), flush=True)

        ans = input()
        if ans == "CORRECT":
            break

        ans = list(ans)
        for i in range(n):
            if ans[i] == "_":
                curr[i] += 1
