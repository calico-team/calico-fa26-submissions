import sys


def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    iterator = iter(input_data)
    T = int(next(iterator))

    out = []

    for _ in range(T):
        N = int(next(iterator))
        L = [int(next(iterator)) for _ in range(N)]
        R = [int(next(iterator)) for _ in range(N)]

        ans = 0
        fixed_bit = [0] * 30

        flex_state = None
        has_full = False

        # Group intervals by their split bit b_i = msb(L_i ^ R_i)
        split_buckets = [[] for _ in range(30)]

        for i in range(N):
            l, r = L[i], R[i]
            if l == r:
                for b in range(30):
                    fixed_bit[b] ^= (l >> b) & 1
            else:
                diff = l ^ r
                bi = diff.bit_length() - 1
                # Bits above bi are fixed for interval i
                prefix = (l >> (bi + 1)) << (bi + 1)
                for b in range(bi + 1, 30):
                    fixed_bit[b] ^= (prefix >> b) & 1

                l_rem = l - prefix
                r_rem = r - prefix
                split_buckets[bi].append((l_rem, r_rem))

        # Process bits from 29 down to 0
        for b in range(29, -1, -1):
            if has_full:
                ans |= 1 << b
                continue

            new_splits = split_buckets[b]
            num_new = len(new_splits)

            if flex_state is None:
                if num_new >= 2:
                    ans |= (1 << (b + 1)) - 1
                    has_full = True
                elif num_new == 1:
                    l_rem, r_rem = new_splits[0]
                    fb = fixed_bit[b]
                    ans |= 1 << b
                    if fb == 0:
                        flex_state = ("LO", r_rem - (1 << b))
                    else:
                        flex_state = ("HI", l_rem)
                else:
                    ans |= fixed_bit[b] << b
            else:
                if num_new >= 1:
                    # Combining active state with new split creates >= 2 flexible intervals
                    ans |= (1 << (b + 1)) - 1
                    has_full = True
                else:
                    fb = fixed_bit[b]
                    st_type = flex_state[0]

                    if st_type == "LO":
                        r_rem = flex_state[1]
                        if fb == 1:
                            ans |= (1 << (b + 1)) - 1
                            has_full = True
                        else:
                            ans |= 1 << b
                            r_next = r_rem & ((1 << b) - 1)
                            flex_state = ("LO", r_next)

                    elif st_type == "HI":
                        l_rem = flex_state[1]
                        if fb == 0:
                            ans |= (1 << (b + 1)) - 1
                            has_full = True
                        else:
                            ans |= 1 << b
                            l_next = l_rem & ((1 << b) - 1)
                            flex_state = ("HI", l_next)

        out.append(str(ans))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()