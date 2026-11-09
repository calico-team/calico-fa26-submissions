def solve(N, R, A):
    q = []
    head = 0
    for t in A:
        while head < len(q) and q[head] <= t:
            head += 1
        if len(q) - head == 2:
            return "NO"
        if len(q) - head == 0:
            q.append(t + R)
        else:
            q.append(q[-1] + R)
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