def solve(N, R, A):
    for req in range(1,N):
        if A[req]-A[req-1]<R:
            return "NO"
    else:
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
