import sys


def msb(x: int) -> int:
    return x.bit_length() - 1 if x > 0 else -1


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
        buckets = [[] for _ in range(30)]
        fixed_xor = 0
        has_full = False

        for i in range(N):
            l, r = L[i], R[i]
            if l == r:
                fixed_xor ^= l
            else:
                diff = l ^ r
                b = msb(diff)
                prefix = (l >> (b + 1)) << (b + 1)
                fixed_xor ^= prefix
                l -= prefix
                r -= prefix

                mask_full = (1 << (b + 1)) - 1
                if l == 0 and r == mask_full:
                    has_full = True
                    ans |= mask_full
                elif l == 0:
                    buckets[b].append(("FREE_LO", r - (1 << b)))
                elif r == mask_full:
                    buckets[b].append(("FREE_HI", l))
                else:
                    buckets[b].append(("ARBITRARY", l, r - (1 << b)))

        fixed_bits = [(fixed_xor >> b) & 1 for b in range(30)]

        for b in range(29, -1, -1):
            if has_full:
                ans |= 1 << b
                continue

            choice_list = buckets[b]
            f_bit = fixed_bits[b]

            if not choice_list:
                ans |= f_bit << b
                continue

            target_parity = 1 ^ f_bit

            has_free = any(
                item[0] in ("FREE_LO", "FREE_HI") for item in choice_list
            )

            if len(choice_list) >= 2 and has_free:
                ans |= (1 << (b + 1)) - 1
                has_full = True
                continue

            if len(choice_list) == 1:
                ans |= 1 << b
                item = choice_list[0]
                itype = item[0]

                if itype == "FREE_LO":
                    r_val = item[1]
                    if target_parity == 0:
                        ans |= (1 << b) - 1
                        has_full = True
                    else:
                        nb = msb(r_val)
                        if nb >= 0:
                            buckets[nb].append(
                                ("FREE_LO", r_val - (1 << nb))
                            )
                elif itype == "FREE_HI":
                    l_val = item[1]
                    if target_parity == 1:
                        ans |= (1 << b) - 1
                        has_full = True
                    else:
                        diff = ((1 << b) - 1) ^ l_val
                        nb = msb(diff)
                        if nb >= 0:
                            prefix = (l_val >> (nb + 1)) << (nb + 1)
                            for bit_k in range(nb + 1, b):
                                fixed_bits[bit_k] ^= (l_val >> bit_k) & 1
                            l_next = l_val - prefix
                            buckets[nb].append(("FREE_HI", l_next))
                elif itype == "ARBITRARY":
                    l_val, r_val = item[1], item[2]
                    if target_parity == 0:
                        diff = ((1 << b) - 1) ^ l_val
                        nb = msb(diff)
                        if nb >= 0:
                            prefix = (l_val >> (nb + 1)) << (nb + 1)
                            for bit_k in range(nb + 1, b):
                                fixed_bits[bit_k] ^= (l_val >> bit_k) & 1
                            l_next = l_val - prefix
                            buckets[nb].append(("FREE_HI", l_next))
                    else:
                        nb = msb(r_val)
                        if nb >= 0:
                            buckets[nb].append(
                                ("FREE_LO", r_val - (1 << nb))
                            )

            else:
                ans |= 1 << b
                candidates = []
                for idx, item in enumerate(choice_list):
                    l_val, r_val = item[1], item[2]
                    diff0 = ((1 << b) - 1) ^ l_val
                    b0 = msb(diff0)
                    b1 = msb(r_val)
                    candidates.append((b0, b1, l_val, r_val))

                best_b = -1
                best_idx = -1
                best_opt = -1
                for idx, (b0, b1, l_val, r_val) in enumerate(candidates):
                    if b0 > best_b:
                        best_b = b0
                        best_idx = idx
                        best_opt = 0
                    if b1 > best_b:
                        best_b = b1
                        best_idx = idx
                        best_opt = 1

                choices = [0] * len(candidates)
                for idx, (b0, b1, l_val, r_val) in enumerate(candidates):
                    if idx == best_idx:
                        choices[idx] = best_opt
                    else:
                        choices[idx] = 0 if b0 >= b1 else 1

                curr_parity = sum(choices) % 2
                if curr_parity != target_parity:
                    flip_idx = 0 if best_idx != 0 else 1
                    choices[flip_idx] ^= 1

                for idx, (b0, b1, l_val, r_val) in enumerate(candidates):
                    ch = choices[idx]
                    if ch == 0:
                        nb = b0
                        if nb >= 0:
                            prefix = (l_val >> (nb + 1)) << (nb + 1)
                            for bit_k in range(nb + 1, b):
                                fixed_bits[bit_k] ^= (l_val >> bit_k) & 1
                            l_next = l_val - prefix
                            buckets[nb].append(("FREE_HI", l_next))
                    else:
                        nb = b1
                        if nb >= 0:
                            buckets[nb].append(
                                ("FREE_LO", r_val - (1 << nb))
                            )

        out.append(str(ans))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()