import sys


def max_xor_intervals(A, B, N):
    fixed_parity = [0] * 30
    splits = [[] for _ in range(30)]

    for i in range(N):
        a, b_val = A[i], B[i]
        if a == b_val:
            for bit in range(30):
                fixed_parity[bit] ^= (a >> bit) & 1
        else:
            diff = a ^ b_val
            msb_b = diff.bit_length() - 1
            prefix = (a >> (msb_b + 1)) << (msb_b + 1)
            for bit in range(msb_b + 1, 30):
                fixed_parity[bit] ^= (prefix >> bit) & 1
            splits[msb_b].append((a - prefix, b_val - prefix))

    ans = 0
    state = 0  # 0: NONE, 1: FREE, 2: FREE_LO, 3: FREE_HI
    rem_val = 0

    for b in range(29, -1, -1):
        if state == 1:
            ans |= (1 << (b + 1)) - 1
            break

        num_s = len(splits[b])

        if state == 0:
            if num_s >= 2:
                ans |= (1 << (b + 1)) - 1
                break
            elif num_s == 1:
                l_rem, r_rem = splits[b][0]
                ans |= 1 << b
                p = fixed_parity[b]
                if p == 0:
                    state = 2  # FREE_LO
                    rem_val = r_rem - (1 << b)
                else:
                    state = 3  # FREE_HI
                    rem_val = l_rem
            else:
                ans |= fixed_parity[b] << b

        elif state == 2:  # FREE_LO
            if num_s >= 1:
                ans |= (1 << (b + 1)) - 1
                break
            else:
                p = fixed_parity[b]
                if p == 1:
                    ans |= (1 << (b + 1)) - 1
                    break
                else:
                    if rem_val >= (1 << b):
                        ans |= 1 << b
                        rem_val -= 1 << b
                    else:
                        ans |= (1 << (b + 1)) - 1
                        break

        elif state == 3:  # FREE_HI
            if num_s >= 1:
                ans |= (1 << (b + 1)) - 1
                break
            else:
                p = fixed_parity[b]
                if p == 0:
                    ans |= (1 << (b + 1)) - 1
                    break
                else:
                    if rem_val < (1 << b):
                        ans |= 1 << b
                    else:
                        ans |= (1 << (b + 1)) - 1
                        break

    return ans


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

        best_ans = 0

        # Evaluate over all candidate interval powers K in [0..30]
        for K in range(31):
            if K > 0:
                mask = (1 << K) - 1
                valid_K = False
                for i in range(N):
                    if (R[i] >> K) > (L[i] >> K) or (
                        (L[i] & mask) == 0 and (R[i] & mask) == mask
                    ):
                        valid_K = True
                        break
                if not valid_K:
                    continue

            A = [L[i] >> K for i in range(N)]
            B = [R[i] >> K for i in range(N)]

            top_xor = max_xor_intervals(A, B, N)

            if K == 0:
                cand = top_xor
            else:
                cand = (top_xor << K) | ((1 << K) - 1)

            if cand > best_ans:
                best_ans = cand

        out.append(str(best_ans))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()