import sys
input = sys.stdin.readline

for case in range(int(input())):
    n, r = map(int, input().split())
    times = list(map(int, input().split()))
    diff = []
    past = 0
    for i in times:
        diff.append(i - past)
        past = i
    charges = 2
    idx = 0
    work = True
    last = float('inf')
    for next in diff:
        idx += next
        while last + r <= idx:
            last = last + r
            charges += 1
            if charges == 2:
                last = float('inf')
                break
        if (charges > 0):
            charges -= 1
            last = idx if last == float('inf') else last
        else:
            work = False
            break
    sys.stdout.write("YES\n" if work else "NO\n")