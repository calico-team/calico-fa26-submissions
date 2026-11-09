import sys

def ewrgji(L, R):
    res = []
    while L <= R:
        if L > 0:
            b = (L & -L).bit_length() - 1
        else:
            b = 62
            
        while L + (1 << b) - 1 > R:
            b -= 1
            
        res.append((L, b))
        L += 1 << b
    return res

def main():
    dataforinputla = sys.stdin.read().split()
    if not dataforinputla:
        return
        
    T = int(dataforinputla[0])
    idx = 1
    out = []
    
    for _ in range(T):
        N = int(dataforinputla[idx])
        idx += 1
        
        L = [int(x) for x in dataforinputla[idx : idx + N]]
        idx += N
        
        R = [int(x) for x in dataforinputla[idx : idx + N]]
        idx += N
        
        S = [(0, 0)]
        for i in range(N):
            intervals_i = ewrgji(L[i], R[i])
            next_S = []
            
            for start1, b1 in S:
                for start2, b2 in intervals_i:
                    if b1 > b2:
                        nb = b1
                    else:
                        nb = b2
                        
                    nstart = (start1 ^ start2) & (~((1 << nb) - 1))
                    next_S.append((nstart, nb))
                    
            next_S.sort(key=lambda x: x[1], reverse=True)
            
            S = []
            for start, b in next_S:
                covered = False
                for s_start, s_b in S:
                    if (start >> s_b) == (s_start >> s_b):
                        covered = True
                        break
                if not covered:
                    S.append((start, b))
                    
        ans = 0
        for start, b in S:
            ans = max(ans, start + (1 << b) - 1)
        out.append(str(ans))
        
    print('\n'.join(out))

if __name__ == '__main__':
    main()
