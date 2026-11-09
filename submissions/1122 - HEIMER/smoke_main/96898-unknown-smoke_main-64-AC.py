def solve(N, R, A):
    smokes = 2
    q = []

    for req in A:
        while q and q[0] <= req:
            smokes += 1
            q.pop(0)

        if smokes == 0:
            return "NO"

        smokes -= 1
        nxt = (q[-1] if q else req) + R
        q.append(nxt)

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