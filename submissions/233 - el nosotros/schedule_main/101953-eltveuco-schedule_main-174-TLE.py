

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
        
    A = [1 if x else 0 for x in P]
    S = {}
    for j in range(M):
        V = [(D[i], i) for i in range(1, N + 1) if A[i - 1] == 0]
        V.sort(key=lambda x: x[0], reverse = True)
        
        if not V:
            break
        
        KV = [v[1] for v in V[:K]] 
        S[j] = KV
        
        for TC in KV:
            A[TC - 1] -= 1
            for UC in U[TC]:
                A[UC - 1] -= 1
    total = sum(len(C) for C in S.values())
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