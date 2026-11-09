def solve(N, R, A):
    recharges = []
    for t in A:
        while recharges and recharges[0] <= t:
            recharges.pop(0)
        if len(recharges) == N:
            return "NO"
        recharges.append(t + R)
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