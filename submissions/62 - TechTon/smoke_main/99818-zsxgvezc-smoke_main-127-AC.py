def solve(N, R, A):
    
    ch = 0
    for t in A:
        if ch-t > R:
            return "NO"
        ch = max(ch, t) + R

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
