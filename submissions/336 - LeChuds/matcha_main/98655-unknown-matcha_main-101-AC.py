import sys

input = sys.stdin.readline

def join(a, b):
    return a | b | ((1 << (a & b).bit_length()) - 1)

def solve(N: int, L: list[int], R: list[int]) -> int:
    groups = [[] for _ in range(30)]
    x = 0
    for l, r in zip(L, R):
        x ^= l
        if l != r:
            groups[(l ^ r).bit_length() - 1].append((l, r))
    for b in range(29, -1, -1):
        if groups[b]:
            mask = (1 << b) - 1
            c0, c1 = 0, -1
            for l, r in groups[b]:
                x ^= l & mask
                a, z = mask - (l & mask), r & mask
                c0, c1 = max(join(c0, a), join(c1, z)), max(join(c1, a), join(c0, z))
            side = 1 ^ (x >> b & 1)
            x |= 1 << b
            if (len(groups[b]) - side) & 1:
                x ^= mask
            c = c1 if side else c0
            if c == mask or not any(groups[:b]):
                return x | join(x & mask, c)
            if c:
                groups[c.bit_length() - 1].append((0, c))
    return x

def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        L = list(map(int, input().split()))
        R = list(map(int, input().split()))
        print(solve(N, L, R))

if __name__ == '__main__':
    main()
