import sys
inp = [line.strip() for line in sys.stdin]
T = int(inp[0])

for i in range(1, len(inp), 2):
    n, r = map(int, inp[i].split()) # num smoke req, seconds for recharge
    a = list(map(int, inp[i+1].split())) # time each req
    # print(n, r, a)

    smokes = [2, 0]
    ans = "YES"
    for j in range(n):
        req = a[j]
        while smokes[0] < 2 and smokes[1] + r <= req:
            smokes[0] = smokes[0]+1
            smokes[1] += r
        if smokes[0] > 0:
            smokes[0] -= 1
            smokes[1] = req
        else:
            ans = "NO"
    print(ans)
