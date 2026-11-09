def solve(N, R, A):
    possibility=True
    for request in range(1,N):
        if A[request]-A[request-1]<R:
            possibility=False
    if possibility:
        return "YES"
    else:
        return "NO"


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
