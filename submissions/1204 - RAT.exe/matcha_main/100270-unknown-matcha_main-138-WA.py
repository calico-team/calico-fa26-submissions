def solve(N: int, L: list[int], R: list[int]) -> int:
    
    fx = 0          
    rs = []        
    for l, r in zip(L, R):
        if l == r:
            fx ^= l
        else:
            rs.append((l, r))
    while rs:
        H = max((l ^ r).bit_length() for l, r in rs) - 1
        X = fx
        cnt = 0
        idx = -1
        for i, (l, r) in enumerate(rs):
            X ^= l
            if ((l ^ r).bit_length() - 1) == H:
                cnt += 1
                idx = i
        if cnt >= 2:
            return ((X >> (H + 1)) << (H + 1)) | ((1 << (H + 1)) - 1)
        l, r = rs[idx]
        c = 1 ^ ((X >> H) & 1)      
        P = (r >> H) << H           
        if c == 1:
            nl, nr = P, r
        else:
            nl, nr = l, P - 1

        if nl == nr:
            fx ^= nl
            rs[idx] = rs[-1]
            rs.pop()
        else:
            rs[idx] = (nl, nr)
    return fx

def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        L = list(map(int, input().split()))
        R = list(map(int, input().split()))
        print(solve(N, L, R))

if __name__ == '__main__':
    main()
