from math import isqrt
_TBL = bytes([0]) + bytes([1]) * 255
_BITS = [tuple(b for b in range(8) if v >> b & 1) for v in range(256)]
def _solve(N, M, Q, earthquakes):
    Mb = (M + 7) >> 3
    Mp = Mb << 3
    res = [0] * (N * M)
    U = bytearray(b'\xff') * (N * Mb)
    masks = {}
    remaining = N * M
    fb = int.from_bytes
    for i in range(Q - 1, -1, -1):
        R, C, P = earthquakes[i]
        mk = masks.get(P)
        if mk is None:
            parts = []
            for t in range(2 * P, -1, -1):
                d = t - P
                if d < 0:
                    d = -d
                w = isqrt(P * P - d * d)
                parts.append('0' * (Mp - P - w - 1) + '1' * (2 * w + 1) + '0' * (P - w))
            mk = int(''.join(parts), 2)
            masks[P] = mk
        a = (R - P) * Mb
        b = (R + P + 1) * Mb
        win = fb(U[a:b], 'little')
        new = win & (mk << (C - P))
        if not new:
            continue
        U[a:b] = (win ^ new).to_bytes(b - a, 'little')
        PP = P * P + 1
        data = new.to_bytes(b - a, 'little')
        flags = data.translate(_TBL)
        base0 = a << 3
        cnt = 0
        bi = flags.find(1)
        while bi >= 0:
            base = base0 + (bi << 3)
            for bt in _BITS[data[bi]]:
                pos = base + bt
                r, c = divmod(pos, Mp)
                res[r * M + c] = PP - (r - R) * (r - R) - (c - C) * (c - C)
                cnt += 1
            bi = flags.find(1, bi + 1)
        remaining -= cnt
        if remaining <= 0:
            break
    return [res[r * M:(r + 1) * M] for r in range(N)]
def solve(N, M, Q, earthquakes):
    if N < M:
        E2 = [(c, r, p) for r, c, p in earthquakes]
        g = _solve(M, N, Q, E2)
        return [list(col) for col in zip(*g)]
    return _solve(N, M, Q, earthquakes)
def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        earthquakes = []
        for i in range(Q):
            X, Y, P = map(int, input().split())
            earthquakes.append((X, Y, P))
        answer = solve(N, M, Q, earthquakes)
        for row in answer:
            print(' '.join(map(str, row)))
if __name__ == '__main__':
    main()
