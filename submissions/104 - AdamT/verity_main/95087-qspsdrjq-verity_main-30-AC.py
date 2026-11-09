#!/usr/bin/env python3

T = int(input())

for _ in range(T):
    n, m = [int(n) for n in input().split()]
    cs = [c for c in input().split()]
    r = [" " for i in range(n)]
    solved = None
    for c in cs[:-1]:
        solved = False
        print("".join(r).replace(" ", c), flush=True)
        res = input()
        if res == "CORRECT":
            solved = True
        else:
            r = res.replace("_", " ")
        if solved:
            break
    if not solved:
        print("".join(r).replace(" ", cs[-1]), flush=True)
        input()

