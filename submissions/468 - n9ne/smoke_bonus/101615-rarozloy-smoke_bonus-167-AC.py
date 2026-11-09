def solve(N, R, A):
    pending = []
    for t in A:
        while pending and pending[0] <= t:
            pending.pop(0)
        if len(pending) == 2:
            return "NO"
        start = pending[-1] if pending else t
        pending.append(start + R)
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