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

        # p_i : maior bit onde L e R diferem, -1 se iguais
        diff = L ^ R
        p = np.full(n, -1, dtype=np.int64)
        nz = diff != 0
        if np.any(nz):
            # bit_length - 1
            p[nz] = np.floor(np.log2(diff[nz].astype(np.float64))).astype(np.int64)
            # correção exata com bit_length via python para segurança
            for idx in np.where(nz)[0]:
                p[idx] = int(diff[idx]).bit_length() - 1

        # Máscaras M_b e constantes C_b
        M = [0] * 30
        C = [0] * 30
        total_bits = ((n + 7) // 8) * 8
        for b in range(30):
            Lb = ((L >> b) & 1).astype(np.uint8)
            Rb = ((R >> b) & 1).astype(np.uint8)
            coeff = ((p == b) | ((p > b) & (Lb != Rb))).astype(np.uint8)
            # packbits: i=0 é o bit mais significativo
            packed = np.packbits(coeff).tobytes()
            M[b] = int.from_bytes(packed, 'big') if packed else 0
            # constante: Lb para p != b, 0 para p == b
            const = np.where(p == b, 0, Lb)
            C[b] = int(np.sum(const) & 1)

        # Base: leading_bit -> (mask, rhs)
        basis = {}

        def reduce_mask(mask: int, rhs: int):
            while mask:
                lead = mask.bit_length() - 1
                if lead in basis:
                    bm, br = basis[lead]
                    mask ^= bm
                    rhs ^= br
                else:
                    break
            return mask, rhs

        def try_add(basis_dict, mask: int, rhs: int):
            # retorna (novo_dict, ok)
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
            return True  # independente -> consistente

        ans = 0
        finished = False

        # candidatos à libertação por bit: pré-calcular p_i > b
        # para o teste rápido usamos listas de índices quando n é pequeno,
        # senão usamos contagem
        for b in range(29, -1, -1):
            if finished:
                break
            # tenta 1 com libertação, depois 1 sem, depois 0 com libertação
            # equação sem libertação: M_b . s = desejado ^ C_b
            # com libertação: M_b . s = desejado ^ C_b ^ 1

            def check_free(desired: int):
                # sistema tentativo = basis + equação com flip
                rhs_flip = desired ^ C[b] ^ 1
                nb, ok = try_add(basis, M[b], rhs_flip)
                if not ok:
                    return False
                # candidatos i com p_i > b
                # L_b == 0 -> pode ser s_i=0 ; R_b == 1 -> pode ser s_i=1
                Lb_all = ((L >> b) & 1)
                Rb_all = ((R >> b) & 1)
                # se muitos candidatos, há variável livre
                # conta rápido com numpy
                mask_cand = (p > b) & ((Lb_all == 0) | (Rb_all == 1))
                cnt = int(np.sum(mask_cand))
                if cnt > len(nb):
                    return True
                if cnt == 0:
                    return False
                # testa um a um (cnt <= 30)
                idxs = np.where(mask_cand)[0]
                for idx in idxs:
                    i = int(idx)
                    e = 1 << (total_bits - 1 - i)
                    vals = []
                    if Lb_all[i] == 0:
                        vals.append(0)
                    if Rb_all[i] == 1:
                        vals.append(1)
                    for v in vals:
                        if can_set(nb, e, v):
                            return True
                return False

            # 1 com libertação ?
            if check_free(1):
                ans |= (1 << b)
                ans |= (1 << b) - 1  # resto tudo 1
                finished = True
                break

            # 1 sem libertação ?
            nb1, ok1 = try_add(basis, M[b], 1 ^ C[b])
            if ok1:
                ans |= (1 << b)
                basis = nb1
                continue

            # 0 com libertação ?
            if check_free(0):
                # bit 0, resto tudo 1
                ans |= (1 << b) - 1
                finished = True
                break

            # 0 sem libertação (tem que ser possível)
            nb0, ok0 = try_add(basis, M[b], 0 ^ C[b])
            if ok0:
                basis = nb0
                # bit 0, segue
            else:
                # não deveria acontecer; por segurança, fixa 0
                pass

        out_lines.append(str(ans))

    sys.stdout.write("\n".join(out_lines))

if __name__ == "__main__":
    solve()