import sys

B = 30


def maximize_with_basis(base, numbers):
    basis = [0] * B

    for value in numbers:
        x = value
        for bit in range(B - 1, -1, -1):
            if not ((x >> bit) & 1):
                continue
            if basis[bit]:
                x ^= basis[bit]
            else:
                basis[bit] = x
                break

    answer = base
    for bit in range(B - 1, -1, -1):
        if basis[bit]:
            answer = max(answer, answer ^ basis[bit])
    return answer


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return

    pos = 0
    t = data[pos]
    pos += 1
    output = []

    for _ in range(t):
        n = data[pos]
        pos += 1

        left = data[pos:pos + n]
        pos += n
        right = data[pos:pos + n]
        pos += n

        candidates = []
        for l, r in zip(left, right):
            candidates.extend((l, r))
            if l + 1 < r:
                candidates.append(l + 1)
            if r - 1 > l:
                candidates.append(r - 1)

        output.append(str(maximize_with_basis(0, candidates)))

    sys.stdout.write("\n".join(output) + "\n")


if __name__ == "__main__":
    main()
