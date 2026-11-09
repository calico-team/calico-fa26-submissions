def solve(N: int, L: list[int], R: list[int]) -> int:
    """
    Returns the maximum possible value of X, Big Ben's matcha enjoyment.

    N: the days in Big Ben's life
    L: the lower bound of enjoyment from each store 
    R: the upper bound of enjoyment from each store
    """
    memo = {}

    def dfs(bit, halat):
        if bit == -1:
            return 0
        halat_tuple = tuple(halat)
        if (bit, halat_tuple) in memo:
            return memo[(bit, halat_tuple)]
        pakka_xor = 0
        jeetne_wale = []
        alag_hone_wale = []
        for i in range(N):
            mojooda = halat[i]
            if mojooda == 2:
                neeche_bit = (L[i] >> bit) & 1
                upar_bit = (R[i] >> bit) & 1
                if neeche_bit == upar_bit:
                    pakka_xor ^= neeche_bit
                else:
                    alag_hone_wale.append(i)
            elif mojooda == 0:
                neeche_bit = (L[i] >> bit) & 1
                if neeche_bit == 1:
                    pakka_xor ^= 1
                else:
                    jeetne_wale.append(i)
            elif mojooda == 1:
                upar_bit = (R[i] >> bit) & 1
                if upar_bit == 1:
                    jeetne_wale.append(i)
        if len(jeetne_wale) >= 1 and (
            len(jeetne_wale) + len(alag_hone_wale) >= 2):
            jawab = (1 << (bit + 1)) - 1
            memo[(bit, halat_tuple)] = jawab
            return jawab
        if len(jeetne_wale) == 1 and len(alag_hone_wale) == 0:
            idx = jeetne_wale[0]
            jeetne_bit = 1 if halat[idx] == 0 else 0
            jawab_jeet = (
                ((pakka_xor ^ jeetne_bit) << bit)
                | ((1 << bit) - 1)
            )
            if (pakka_xor ^ jeetne_bit) == 1:
                memo[(bit, halat_tuple)] = jawab_jeet
                return jawab_jeet
            else:
                nayi_halat = list(halat)
                nayi_halat[idx] = 0 if halat[idx] == 0 else 1
                jawab_safe = (1 << bit) | dfs(bit - 1, nayi_halat)
                jawab = max(jawab_jeet, jawab_safe)
                memo[(bit, halat_tuple)] = jawab
                return jawab
        if len(jeetne_wale) == 0 and len(alag_hone_wale) == 0:
            jawab = (pakka_xor << bit) | dfs(bit - 1, halat)
            memo[(bit, halat_tuple)] = jawab
            return jawab
        jawab = -1
        if len(alag_hone_wale) == 1:
            combinations = [(0,), (1,)]
        else:
            tadaad = len(alag_hone_wale)
            zaroori_parity = 1 ^ pakka_xor
            combinations = [[0] * tadaad, [0] * tadaad]
            combinations[0][0] = zaroori_parity
            combinations[1][0] = 1 ^ zaroori_parity
            combinations[1][1] = 1
        for comb in combinations:
            nayi_halat = list(halat)
            mojooda_xor = pakka_xor
            for i, idx in enumerate(alag_hone_wale):
                bit_chuno = comb[i]
                nayi_halat[idx] = 0 if bit_chuno == 0 else 1
                mojooda_xor ^= bit_chuno
            candidate = (
                (mojooda_xor << bit)
                | dfs(bit - 1, nayi_halat)
            )
            jawab = max(jawab, candidate)
        memo[(bit, halat_tuple)] = jawab
        return jawab

    shuru_halat = [2] * N
    return dfs(29, shuru_halat)

def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        L = list(map(int, input().split()))
        R = list(map(int, input().split()))
        print(solve(N, L, R))

if __name__ == '__main__':
    main()
