import sys
from math import isqrt

MAX_SQ = 250005
SQRT_TBL = [0] * MAX_SQ
for _i in range(MAX_SQ):
    SQRT_TBL[_i] = isqrt(_i)

def solve():
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    ptr = 0
    T = int(data[ptr]); ptr += 1
    out = []
    
    sqrt_tbl = SQRT_TBL
    
    for _ in range(T):
        n = int(data[ptr]); m = int(data[ptr+1]); q = int(data[ptr+2]); ptr += 3
        
        quakes = []
        for _ in range(q):
            r = int(data[ptr]); c = int(data[ptr+1]); p = int(data[ptr+2]); ptr += 3
            quakes.append((r, c, p))
        
        transposed = n > m
        if transposed:
            n, m = m, n
            quakes = [(c, r, p) for (r, c, p) in quakes]
        
        all_ones = (1 << m) - 1
        row_bits = [all_ones] * n
        row_min = [0] * n
        row_max = [m - 1] * n
        
        result = [0] * (n * m)
        
        for qi in range(q - 1, -1, -1):
            er, ec, p = quakes[qi]
            ps = p * p
            
            r_lo = er - p
            if r_lo < 0: r_lo = 0
            r_hi = er + p
            if r_hi >= n: r_hi = n - 1
            
            for r in range(r_lo, r_hi + 1):
                bits = row_bits[r]
                if bits == 0:
                    continue
                
                dr = r - er
                rem_sq = ps - dr * dr
                if rem_sq < 0:
                    continue
                
                max_dc = sqrt_tbl[rem_sq]
                L = ec - max_dc
                if L < 0: L = 0
                R = ec + max_dc
                if R >= m: R = m - 1
                if L > R:
                    continue
                
                if row_max[r] < L or row_min[r] > R:
                    continue
                
                mask = ((1 << (R - L + 1)) - 1) << L
                target = bits & mask
                
                if target == 0:
                    continue
                
                row_bits[r] = bits & ~mask
                
                base = r * m
                dr_sq = dr * dr
                t = target
                while t:
                    low = t & -t
                    c = low.bit_length() - 1
                    dc = c - ec
                    result[base + c] = ps - dr_sq - dc * dc + 1
                    t ^= low
                
                new_bits = row_bits[r]
                if new_bits == 0:
                    row_min[r] = m
                    row_max[r] = -1
                else:
                    row_min[r] = (new_bits & -new_bits).bit_length() - 1
                    row_max[r] = new_bits.bit_length() - 1
        
        if not transposed:
            for r in range(n):
                base = r * m
                out.append(" ".join(map(str, result[base:base+m])))
        else:
            for oi in range(m):
                parts = [str(result[oj * m + oi]) for oj in range(n)]
                out.append(" ".join(parts))
    
    sys.stdout.write("\n".join(out))

if __name__ == "__main__":
    solve()