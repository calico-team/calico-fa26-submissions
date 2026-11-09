def solve(N: int, K: int, L: list):
    grps = {}
    for X, Y, Z, D in L:
        S = X + Y
        if S not in grps:
            grps[S] = ([], [])
        if D == 'E':
            grps[S][0].append((X, Z))
        else:
            grps[S][1].append((X, Z))
            
    total_colli = 0
    MAX_Z = 100005
    
    def add(bit, idx, val):
        while idx < len(bit):
            bit[idx] += val
            idx += idx & (-idx)
            
    def query(bit, idx):
        s = 0
        while idx > 0:
            s += bit[idx]
            idx -= idx & (-idx)
        return s

    for S, (e_drns, n_drns) in grps.items():
        if not e_drns or not n_drns:
            continue
            
        if K > 100000:
            n_buckets = [[] for _ in range(100005)]
            for X, Z in n_drns:
                if X <= 100000:
                    n_buckets[X].append(Z)
                
            e_buckets = [[] for _ in range(100005)]
            for X, Z in e_drns:
                if X <= 100000:
                    e_buckets[X].append(Z)
                
            bit = [0] * (MAX_Z + 1)
            for x in range(100000, -1, -1):
                for z in n_buckets[x]:
                    add(bit, z + 1, 1)
                for z in e_buckets[x]:
                    total_n = query(bit, MAX_Z)
                    less_eq = query(bit, z + 1)
                    total_colli += (total_n - less_eq)
        else:
            n_buckets = [[] for _ in range(200005)]
            for X, Z in n_drns:
                n_buckets[X].append(Z)
                
            e_buckets = [[] for _ in range(100005)]
            for X, Z in e_drns:
                e_buckets[X].append(Z)
                
            bit = [0] * (MAX_Z + 1)
            for x in range(min(100005, K)):
                for z in n_buckets[x]:
                    add(bit, z + 1, 1)
                    
            max_x = max(max((x for x, _ in e_drns), default=0), max((x for x, _ in n_drns), default=0))
            limit_x = max_x + K
            
            for x in range(limit_x + 1):
                if x <= 100000:
                    for z in e_buckets[x]:
                        total_n = query(bit, MAX_Z)
                        less_eq = query(bit, z + 1)
                        total_colli += (total_n - less_eq)
                
                for z in n_buckets[x]:
                    add(bit, z + 1, -1)
                if x + K <= 200000:
                    for z in n_buckets[x + K]:
                        add(bit, z + 1, 1)
                        
    return N * K - total_colli

def main():
    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        L = []
        for _ in range(N):
            X, Y, Z, D = input().split()
            L.append((int(X), int(Y), int(Z), D))

        print(solve(N, K, L))

if __name__ == '__main__':
    main()
