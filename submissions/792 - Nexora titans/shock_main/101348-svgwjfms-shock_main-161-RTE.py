import sys
import numpy as np

def main():
    dataa = np.array(sys.stdin.buffer.read().split(), dtype=np.int64)
    position = 0
    T = int(dataa[position]); position += 1

    LIM = 1_000_002
    lagg = np.zeros(LIM, dtype=np.int64)
    k = 1
    while (1 << k) < LIM:
        lagg[1 << k:] += 1
        k += 1

    out = []
    for _ in range(T):
        N = int(dataa[position]); M = int(dataa[position + 1]); Q = int(dataa[position + 2]); position += 3
        E = dataa[position:position + 3 * Q].reshape(Q, 3)
        position += 3 * Q
        Ra = E[:, 0]; Ca = E[:, 1]; Pa = E[:, 2]

        K = int(lagg[M]) + 1
        tablet = np.zeros((K, N, M), dtype=np.int32)

        r1 = Ra.tolist(); Cl = Ca.tolist(); Pl = Pa.tolist()
        for t in range(Q):
            R = r1[t]; C = Cl[t]; P = Pl[t]
            dr = np.arange(-P, P + 1, dtype=np.int64)
            s = P * P - dr * dr
            w = np.sqrt(s).astype(np.int64)
            w += ((w + 1) * (w + 1) <= s)
            w -= (w * w > s)
            length = 2 * w + 1
            kk = lagg[length]
            rows = dr + R
            l = C - w
            r = C + w
            tablet[kk, rows, l] = t + 1
            tablet[kk, rows, r - (1 << kk) + 1] = t + 1

        # push down
        for k in range(K - 1, 0, -1):
            width = M - (1 << k) + 1
            if width <= 0:
                continue
            half = 1 << (k - 1)
            src = tablet[k][:, :width]
            a = tablet[k - 1][:, :width]
            np.maximum(a, src, out=a)
            b = tablet[k - 1][:, half:half + width]
            np.maximum(b, src, out=b)

        index = tablet[0].astype(np.int64)
        Ra1 = np.concatenate(([0], Ra))
        Ca1 = np.concatenate(([0], Ca))
        Pa1 = np.concatenate(([0], Pa))
        rr = np.arange(N, dtype=np.int64)[:, None]
        cc = np.arange(M, dtype=np.int64)[None, :]
        dist2 = (rr - Ra1[index]) ** 2 + (cc - Ca1[index]) ** 2
        val = Pa1[index] ** 2 - dist2 + 1
        val[index == 0] = 0

        for row in val.tolist():
            out.append(' '.join(map(str, row)))

    sys.stdout.write('\n'.join(out) + '\n')

main()