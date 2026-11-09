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
        
        basis = [0] * 32
        
        def insert_basis(mask):
            for i in range(31, -1, -1):
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
                msb = (li ^ ri).bit_length() - 1
                current_xor ^= (li >> (msb + 1)) << (msb + 1)
                insert_basis((1 << (msb + 1)) - 1)

        ans = current_xor
        for b in range(31, -1, -1):
            if (ans ^ basis[b]) > ans:
                ans ^= basis[b]
                    
        out.append(str(ans))
        
    print("\n".join(out))

if __name__ == "__main__":
    solve()
