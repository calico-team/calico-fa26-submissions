import sys

def get_branch_intervals(lo, hi, b, val):
    """Return list of [start, end] intervals inside [lo,hi] where bit b == val."""
    period = 1 << (b + 1)
    half = 1 << b
    base = val * half
    res = []
    k_min = lo // period
    k_max = hi // period
    # extend by 1 on each side to be safe
    for kk in range(k_min - 1, k_max + 2):
        if kk < 0:
            continue
        a = kk * period + base
        e = a + half - 1
        cl = max(lo, a)
        ch = min(hi, e)
        if cl <= ch:
            res.append((cl, ch))
    return res


def solve():
    data = sys.stdin.buffer.read().split()
    pos = 0
    T = int(data[pos]); pos += 1
    out = []

    for _ in range(T):
        n = int(data[pos]); pos += 1
        L = [int(data[pos + i]) for i in range(n)]; pos += n
        R = [int(data[pos + i]) for i in range(n)]; pos += n

        lo = L[:]
        hi = R[:]
        ans = 0

        for b in range(29, -1, -1):
            flex = 0
            forced1 = 0
            info = []  # per day: (can0, can1)

            for i in range(n):
                iv0 = get_branch_intervals(lo[i], hi[i], b, 0)
                iv1 = get_branch_intervals(lo[i], hi[i], b, 1)
                can0 = len(iv0) > 0
                can1 = len(iv1) > 0
                info.append((can0, can1, iv0, iv1))
                if can0 and can1:
                    flex += 1
                elif can1:
                    forced1 += 1

            # Determine the answer bit
            if flex > 0:
                bit = 1
            else:
                bit = forced1 & 1

            if bit:
                ans |= (1 << b)

            # Update intervals
            if flex > 0:
                # We need sum of flexible days' bits ≡ (bit - forced1) mod 2
                need_parity = (bit - forced1) & 1
                # Assign: first flexible day -> need_parity, rest flexible -> 0
                used_flex = False
                new_lo = lo[:]
                new_hi = hi[:]

                for i in range(n):
                    can0, can1, iv0, iv1 = info[i]
                    if can0 and can1:
                        if not used_flex:
                            target = need_parity
                            used_flex = True
                        else:
                            target = 0
                        target_ivs = iv1 if target == 1 else iv0
                        # Union of target_ivs; since original interval is contiguous,
                        # the branch might be multiple intervals. Keep them as one
                        # contiguous block by taking min start and max end
                        # (this is valid because the original interval [lo,hi] is contiguous
                        # and each branch part is a sub-interval; for lower bits we only
                        # need a superset that is still subset of original — but union
                        # may be disjoint. To stay safe, we merge to bounding box only
                        # when the branch produces a single interval; otherwise we keep
                        # the tightest single interval available.)
                        if len(target_ivs) == 1:
                            new_lo[i], new_hi[i] = target_ivs[0]
                        else:
                            # multiple intervals: pick the largest one to maximize freedom
                            best = max(target_ivs, key=lambda t: t[1] - t[0])
                            new_lo[i], new_hi[i] = best
                    elif can1:
                        if len(iv1) == 1:
                            new_lo[i], new_hi[i] = iv1[0]
                        else:
                            best = max(iv1, key=lambda t: t[1] - t[0])
                            new_lo[i], new_hi[i] = best
                    elif can0:
                        if len(iv0) == 1:
                            new_lo[i], new_hi[i] = iv0[0]
                        else:
                            best = max(iv0, key=lambda t: t[1] - t[0])
                            new_lo[i], new_hi[i] = best
                    else:
                        # Should not happen
                        new_lo[i], new_hi[i] = lo[i], lo[i]

                lo, hi = new_lo, new_hi
            # else: all days are forced -> no update required

        out.append(str(ans))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
