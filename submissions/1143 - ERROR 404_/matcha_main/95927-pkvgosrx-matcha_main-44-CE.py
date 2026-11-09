import sys
import numpy as np

def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    it = iter(data)
    t = next(it, 0)
    out_lines = []
    for _ in range(t):
        n = next(it)
        L = np.array([next(it) for _ in range(n)], dtype=np.int64)
        R = np.array([next(it) for _ in range(n)], dtype=np.int64)
        diff = L ^ R
        p = np.full(n, -1, dtype=np.int64)
        nz = np.where(diff != 0)[0]
        for idx in nz:
            p[idx] = int(diff[idx]).bit_length() - 1
        M = [0] * 30
        C = [0] * 30
        total_bits = ((n + 7) // 8) * 8
        for b in range(30):
            Lb = ((L >> b) & 1).astype(np.uint8)
            Rb = ((R >> b) & 1).astype(np.uint8)
            coeff = ((p == b) | ((p > b) & (Lb != Rb))).astype(np.uint8)
            packed = np.packbits(coeff).tobytes()
            M[b] = int.from_bytes(packed, 'big') if packed else 0
            const = np.where(p == b, 0, Lb)
            C[b] = int(np.sum(const) & 1)
        basis = {}
        def try_add(basis_dict, mask: int, rhs: int):
            nd = dict(basis_dict)
            m, r = mask, rhs
            while m:
                lead = m.bit_length() - 1
                if lead in nd:
                    bm, br = nd[lead]
                    m ^= bm
                    r ^= br
                else:
                    break
            if m == 0:
                return nd, (r == 0)
            nd[m.bit_length() - 1] = (m, r)
            return nd, True
        def can_set(basis_dict, mask: int, rhs: int) -> bool:
            m, r = mask, rhs
            while m:
                lead = m.bit_length() - 1
                if lead in basis_dict:
                    bm, br = basis_dict[lead]
                    m ^= bm
                    r ^= br
                else:
                    break
            if m == 0:
                return r == 0
            return True
        ans = 0
        finished = False
        for b in range(29, -1, -1):
            if finished:
                break
            def check_free(desired: int):
                rhs_flip = desired ^ C[b] ^ 1
                nb, ok = try_add(basis, M[b], rhs_flip)
                if not ok:
                    return False
                Lb_all = ((L >> b) & 1)
                Rb_all = ((R >> b) & 1)
                mask_cand = (p > b) & ((Lb_all == 0) | (Rb_all == 1))
                cnt =