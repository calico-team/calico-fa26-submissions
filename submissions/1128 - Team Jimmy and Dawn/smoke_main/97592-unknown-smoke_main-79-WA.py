def solve(N, R, A):
    x1 = 0
    x2 = 0
    for t in A:
        if x1 <= t:
            x1 = t + R
        elif x2 <= t:
            x2 = t + R
        else:
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