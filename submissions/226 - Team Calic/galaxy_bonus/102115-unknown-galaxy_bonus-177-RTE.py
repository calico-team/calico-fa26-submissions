import sys

def solve(N, R, A):
    done = [0] * N
    for i in range(N):
        if i >= 2 and done[i - 2] > A[i]:
            return "NO"
        prev = done[i - 1] if i > 0 else 0
        done[i] = max(A[i], prev) + R
    return "YES"
def main():
    data = sys.stdin.read().split()
    pos = 0
    T = int(data[pos]); pos += 1
    for _ in range(T):
        N = int(data[pos]); R = int(data[pos + 1]); pos += 2
        A = list(map(int, data[pos:pos + N])); pos += N
        print(solve(N, R, A))

if __name__ == "__main__":
    main()