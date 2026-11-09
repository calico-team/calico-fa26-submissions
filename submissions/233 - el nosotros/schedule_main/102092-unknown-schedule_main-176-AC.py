

def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    # YOUR CODE HERE
    U = {i: [] for i in range(1, N+1)}
    for C in range (1, N+1):
        p = P[C - 1]
        if p != 0:
            U[p].append(C)
    
    D = [0] * (N + 1)

    O = []
    stack = [i for i in range(1, N + 1) if P[i-1] == 0]

    while stack:
        c = stack.pop()
        O.append(c)
        stack.extend(U[c])

    for c in reversed(O):
        D[c] = 1 + max((D[u] for u in U[c]), default=0)
        
    avail = [i for i in range(1, N + 1) if P[i-1] == 0]
    total = 0
    
    for _ in range(M):
        if not avail:
            break
        avail.sort(key=lambda c: D[c], reverse=True)
        KV = avail[:K]
        total += len(KV)
        avail = avail[K:]
        for c in KV:
            avail.extend(U[c])
    
    return total

# def find_depth(C, D, U):
#     if D[C] != 0:
#         return D[C]
#     if not U[C]:
#         D[C] = 1
#         return 1
#     M = max(find_depth(u, D, U) for u in U[C])
#     D[C] = 1 + M
#     return D[C]
    
def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()