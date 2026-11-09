import sys
from math import isqrt

def main():
    dataa = sys.stdin.buffer.read().split()
    position = 0
    T = int(dataa[position]); position += 1
    out = []
    for item in range(T):
        N = int(dataa[position]); M = int(dataa[position + 1]); Q = int(dataa[position + 2])
        position += 3
        quak = dataa[position:position + 3 * Q]
        position += 3 * Q

        W = M + 1  
        nxt = list(range(N * W))
        res = [0] * (N * W)
        rem = [M] * N  

        for t in range(Q - 1, -1, -1):
            R = int(quak[3 * t])
            C = int(quak[3 * t + 1])
            P = int(quak[3 * t + 2])
            P2 = P * P
            for d in range(-P, P + 1):
                row = R + d
                if rem[row] == 0:
                    continue
                s = P2 - d * d
                w = isqrt(s)
                base = row * W
                r = base + C + w
                x = base + C - w
                while nxt[x] != x:
                    nxt[x] = nxt[nxt[x]]
                    x = nxt[x]
                while x <= r:
                    d = x - base - C
                    res[x] = s - d * d + 1
                    nxt[x] = x + 1
                    rem[row] -= 1
                    x += 1
                    while nxt[x] != x:
                        nxt[x] = nxt[nxt[x]]
                        x = nxt[x]

        for i in range(N):
            b = i * W
            out.append(' '.join(map(str, res[b:b + M])))

    sys.stdout.write('\n'.join(out) + '\n')

main()