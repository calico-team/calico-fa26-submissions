from bisect import insort_left as bsl
def solve():
    N, R = map(int, input().split())
    S = [int(i) for i in input().split()]

    charges = 2
    
    actionQueue = [[i, 'REQUEST'] for i in S]
    i = 0
    while i < len(actionQueue):
        if actionQueue[i][1] == 'REQUEST':
            if charges == 0:
                print("NO")
                return
            else:
                charges -= 1
                bsl(actionQueue, [actionQueue[i][0] + R, 'RECHARGE'])
        elif actionQueue[i][1] == 'RECHARGE':
            if charges == 0:
                charges += 1
                bsl(actionQueue, [actionQueue[i][0] + R, 'RECHARGE'])
            elif charges == 1:
                charges += 1
        i += 1
    print("YES")

for i in range(int(input())):
    solve()