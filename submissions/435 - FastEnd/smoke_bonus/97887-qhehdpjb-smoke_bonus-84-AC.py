def solve(N, R, A):
    t1 = 0
    t2 = 0
    for x in A:
        while t1 and t1<=x:
            t1 = t2
            t2 = 0
        if t2:
            return "NO"
        if not t1:
            t1 = x+R
        else:
            t2 = t1+R
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
