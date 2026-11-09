import sys

def solve():
    input = sys.stdin.readline
    T = int(input())

    for _ in range(T):
        n = int(input())
        L = list(map(int, input().split()))
        R = list(map(int, input().split()))

        if n == 1:
            print(R[0])
            continue

        low = 0
        high = (1 << 30) - 1

        for i in range(n):
            low ^= L[i]
            high ^= R[i]

        # Maximum possible XOR using interval choices
        ans = 0
        for bit in range(29, -1, -1):
            mask = 1 << bit
            if (ans | mask) <= high:
                ans |= mask

        print(ans)


def read_your_input():
    solve()


if __name__ == "__main__":
    read_your_input()