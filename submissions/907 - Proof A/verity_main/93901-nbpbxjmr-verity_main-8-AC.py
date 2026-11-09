t = int(input())


def do_one():
    n, k = map(int, input().split())
    chars = input().split()
    ans = [""]*n
    for c in chars:
        print(c*n)
        res = input()
        if res == "CORRECT":
            return
        else:
            for i, x in enumerate(res):
                if x != "_":
                    ans[i] = x
    print("".join(ans))
    res = input()
    return

for i in range(t):
    do_one()
