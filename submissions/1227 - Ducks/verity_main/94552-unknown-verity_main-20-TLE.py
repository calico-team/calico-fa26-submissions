from sys import stdin

for _ in range(int(stdin.readline().strip())):
    slen, k = map(int, stdin.readline().split())

    names = stdin.readline().split()

    res = [None for _ in range(slen)]

    for c in names:
        print(c.capitalize() * slen, flush=True)
        s = stdin.readline().strip()
        for j, c2 in enumerate(s):
            if c2 != "_":
                res[j] = c.capitalize()
        if None not in res:
            break

    print("".join(res))
    stdin.readline()  ## CORRECT
