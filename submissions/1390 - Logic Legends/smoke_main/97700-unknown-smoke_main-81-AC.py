from collections import deque
 
 
def solve(N, R, A):
    charges = 2
    pending = deque()
    for a in A:
        while pending and pending[0] <= a:
            pending.popleft()
            charges += 1
        if charges == 0:
            return "NO"
        charges -= 1
        if pending:
            pending.append(pending[-1] + R)
        else:
            pending.append(a + R)
    return "YES"
 
 
def main():
    T = int(input())
    for _ in range(T):
        temp = input().split()
        N = int(temp[0])
        R = int(temp[1])
        A = list(map(int, input().split()))
        print(solve(N, R, A))
 
 
if __name__ == '__main__':
    main()
 