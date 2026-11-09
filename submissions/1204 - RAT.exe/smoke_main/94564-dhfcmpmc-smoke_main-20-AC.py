import sys
from collections import deque

def solve(n, r, a):
    charges = 2
    pending = deque()  

    for t in a:
        
        while pending and pending[0] <= t:
            pending.popleft()
            charges += 1

        if charges == 0:
            return "NO"

        charges -= 1
        
        start = max(t, pending[-1]) if pending else t
        pending.append(start + r)

    return "YES"

def main():
    data = sys.stdin.read().split()
    idx = 0
    t = int(data[idx]); idx += 1
    out = []
    for _ in range(t):
        n, r = int(data[idx]), int(data[idx + 1]); idx += 2
        a = list(map(int, data[idx:idx + n])); idx += n
        out.append(solve(n, r, a))
    print("\n".join(out))

if __name__ == "__main__":
    main()
        
