def solve(N, R, A):
    charge1 = 0
    charge2 = 0
    for t in A:
        earliest = min(charge1, charge2)
        later = max(charge1, charge2)
        if earliest > t:
            return "NO"
        charge1 = later
        charge2 = max(later, t) + R
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