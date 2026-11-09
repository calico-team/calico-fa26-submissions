import sys
from collections import deque

def solution():
    inpt_dat = sys.stdin.read().split()
    if not inpt_dat:
        return
    
    iterations = iter(inpt_dat)
    T = int(next(iterations))
    for items in range(T):
        N = int(next(iterations))
        R = int(next(iterations))
        A = [int(next(iterations)) for _ in range(N)]
        charges = 2
        queue = deque()
        possible = True
        for test in A:
            while queue and queue[0] <= test:
                queue.popleft()
                charges += 1

            if charges > 0:
                charges -= 1
                if not queue:
                    queue.append(test + R)
                else:
                    queue.append(queue[-1] + R)
            else:
                possible = False
                break
        
        if possible:
            print("YES")
        else:
            print("NO")

if __name__ == '__main__':
    solution()