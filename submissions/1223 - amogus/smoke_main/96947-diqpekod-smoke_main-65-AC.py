import sys
input = sys.stdin.readline

for case in range(int(input())):
    n, r = map(int, input().split())
    times = list(map(int, input().split()))
    charges = 2
    next = 0
    going = False
    lastuse = float('inf')
    for i in range(max(times) + 1):
        if lastuse + r == i:
            charges += 1
            lastuse = float('inf') if charges == 2 else i
        if i == times[next]:
            if charges > 0:
                charges -= 1
                if lastuse == float('inf'):
                    lastuse = i
                next += 1
            else:
                going = True
        if going:
            sys.stdout.write("NO\n")
            break
    if not going:
        sys.stdout.write("YES\n")