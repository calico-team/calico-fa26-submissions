#!/usr/bin/env python3

T = int(input())

for _ in range(T):
    n, m = [int(n) for n in input().split()]
    cs = [c for c in input().split()]
    r = [" " for i in range(n)]
    for c in cs[:-1]:
        print(c * n, flush=True)
        res = input()
        if res == "CORRECT":
            r = [c for i in range(n)]
        else:
            for i in range(len(res)):
                if res[i] != "_":
                    r[i] = res[i]
        if " " not in r:
            break
    print("".join(r).replace(" ", cs[-1]), flush=True)
    input()

