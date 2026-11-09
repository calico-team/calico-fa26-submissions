# Source: https://usaco.guide/general/io
def main():
    data = list(map(int, sys.stdin.buffer.read().split()))

    if not data:
        return

    idx = 0
    T = data[idx]
    idx += 1

    out = []

    for _ in range(T):
        if idx + 2 > len(data):
            return

        N = data[idx]
        R = data[idx + 1]
        idx += 2

        if idx + N > len(data):
            return

        A = data[idx:idx + N]
        idx += N

        # Your existing algorithm goes here