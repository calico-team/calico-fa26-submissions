def solve():

    T = int(input("Enter number of test cases: "))

    for i in range(T):

        print("\nTest Case", i + 1)
        N, R = map(int, input("Enter N and R: ").split())
        A = list(map(int, input("Enter smoke request times: ").split()))

        first = 0
        second = 0
        possible = True

        for t in A:
            if t < first:
                possible = False
                break
            first, second = second, max(t, second) + R
        print("Result:", "YES" if possible else "NO")

if __name__ == "__main__":
    solve()