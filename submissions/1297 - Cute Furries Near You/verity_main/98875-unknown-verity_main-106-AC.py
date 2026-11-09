import random

la = lambda x, y: x if x is not None else y

def rfl(l, x):
    l.remove(x)
    return l
1
for _ in range(int(input())):
    n, k = tuple(int(x) for x in input().split())
    ab = input().split()
    known = [None] * n
    p = [ab[:] for _ in range(n)]
    while True:
        r = [random.choice(x) for x in p]
        print(''.join(la(a, b) for a, b in zip(known, r)))
        i = input()
        if i == "CORRECT":
            break
        known = [None if x == '_' else x for x in i]
        p = [rfl(x, c) for x, c in zip(p, r)]