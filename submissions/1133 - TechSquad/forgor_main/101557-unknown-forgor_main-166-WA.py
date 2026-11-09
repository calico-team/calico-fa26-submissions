import sys
import heapq

def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
  adg_deg = [0] * (N + 1)
  nb_xor = [0] * (N + 1)

  for u,v in E:
     adg_deg[u] += 1
     adg_deg[v] += 1
     nb_xor[u] ^= v
     nb_xor[v] ^= u

  leaves = [i for i in range(1, N + 1) if adg_deg[i] == 1]
  heapq.heapify(leaves)
  P = []

  for _ in range(N - 2):
    leaf = heapq.heappop(leaves)
    nb = nb_xor[leaf]
    P.append(nb)
    adg_deg[nb] -= 1
    nb_xor[nb] ^= leaf
    if adg_deg[nb] == 1:
      heapq.heappush(leaves, nb)

  x = 0
  for p in P:
    x ^= p
  return P + [x,x]

def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    if N == 2:
       return [(1,2)]

    P = A[:N - 2]
    parity = A[N - 2] if A[N - 2] != -1 else A[N - 1]
    if -1 in P:
       k = P.index(-1)
       x = parity
       for i,p in enumerate(P):
           if i != k:
              x ^= p
              
       P[k] = x

    deg = [1] * (N + 1)
    for p in P:
      deg[p] += 1

    edges = []
    ptr = 1
    while deg[ptr]!= 1:
     ptr += 1
    leaf = ptr
    for p in P:
      edges.append((leaf, p))
      deg[leaf] -= 1
      if deg[p] == 1 and p < ptr:
        leaf = p
      else:
        ptr += 1
        while deg[ptr] != 1:
            ptr += 1
        leaf = ptr
    edges.append((leaf, N))        
    return edges

def main():
   phase = input()
   N = int(input())
   if phase == 'FIRST' :
       E = []
       for _ in range(N - 1):
           u,v = map(int, input().split())
           E.append((u,v))
       A = solve_phase1(N, E)
       print(' '.join(map(str, A)))        
   else:
         A = list(map(int, input().split()))
         for u,v in solve_phase2(N, A):
             print(u, v)

if __name__ == '__main__':            
      main()