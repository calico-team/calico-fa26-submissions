def solve(N, R, A):
    #rechergin the drop[s ] we REW SUPPOSR TO GET
    c = 0
    for x, y in zip(A, A[2:]):
        if x > c:
            c = x
        c += R
        if c > y:
            return "NO"
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