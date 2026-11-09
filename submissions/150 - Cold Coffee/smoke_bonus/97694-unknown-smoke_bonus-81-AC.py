def solve(N, R, A):
    a=2
    f=None
    s=None
    for i in A:
        while f is not None and f<=i:
            a=a+1
            f=s
            s=None
        if a==0:
            return 'NO'
        a=a-1
        if f is None:
            f=i+R
        else:
            s=f+R
      
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
