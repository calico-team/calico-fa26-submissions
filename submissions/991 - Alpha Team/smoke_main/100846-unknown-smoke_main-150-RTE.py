def solve(N, R, A):
   
    available = 2
    recharge = deque()

    for t in A:

        while recharge and recharge[0] <= t:
            recharge.popleft()
            available += 1

        if available == 0:
            return "NO"

        available -= 1

        if recharge:
            recharge.append(recharge[-1] + R)
        else:
            recharge.append(t + R)

    return "YES" 


def main():
    T = int(input())

    for _ in range(T):
        N, R = map(int, input().split())
        A = list(map(int, input().split()))

        print(solve(N, R, A))


if __name__ == '__main__':
    main()

    


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
