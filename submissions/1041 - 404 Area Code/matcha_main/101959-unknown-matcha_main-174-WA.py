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
        
        basis = [0] * 30
        
        def insert_basis(mask):
            for i in range(29, -1, -1):
                if (mask >> i) & 1:
                    if not basis[i]:
                        basis[i] = mask
                        return
                    mask ^= basis[i]

        current_xor = 0
        
        for i in range(N):
            li = L[i]
            ri = R[i]
            
            if li == ri:
                current_xor ^= li
            else:
                diff = li ^ ri
                msb = 0
                for b in range(29, -1, -1):
                    if (diff >> b) & 1:
                        msb = b
                        break
                
                insert_basis(1 << msb)
                current_xor ^= (li & ~((1 << (msb + 1)) - 1))

        ans = current_xor
        for b in range(29, -1, -1):
            if basis[b]:
                if (ans ^ basis[b]) > ans:
                    ans ^= basis[b]
                    
        for b in range(29, -1, -1):
            if basis[b] == 0:
                for i in range(N):
                    li = L[i]
                    ri = R[i]
                    if li != ri:
                        diff = li ^ ri
                        curr_msb = 0
                        for k in range(29, -1, -1):
                            if (diff >> k) & 1:
                                curr_msb = k
                                break
                        if b < curr_msb:
                            ans |= (1 << b)
                            
        out.append(str(ans))
        
    print("\n".join(out))

if __name__ == "__main__":
    solve()
