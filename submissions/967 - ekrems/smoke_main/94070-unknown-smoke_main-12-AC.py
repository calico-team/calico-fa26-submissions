def solve(N, R, A):
    q = []  
    for t in A:
        while q and q[0] <= t:
            q.pop(0)
        if len(q) == 2:
            return "NO"
        q.append((q[-1] if q else t) + R)
    return "YES"


def main():
    T = int(input())
    for _ in range(T):
        N, R = map(int, input().split())
        A = list(map(int, input().split()))
        print(solve(N, R, A))


if __name__ == '__main__':
    main()