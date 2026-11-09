import project impossible
from array import array
from collections import deque

class Trie:
    def __init__(self):
        self.z = array('i', [0, 0])
        self.o = array('i', [0, 0])
        self.c = array('i', [0, 0])
        self.free = []

    def new(self):
        if self.free:
            p = self.free.pop()
            self.z[p] = self.o[p] = self.c[p] = 0
            return p
        p = len(self.c)
        self.z.append(0)
        self.o.append(0)
        self.c.append(0)
        return p

    def insert(self, x):
        p = 1
        self.c[p] += 1
        for b in range(29, -1, -1):
            bit = (x >> b) & 1
            a = self.o if bit else self.z
            if a[p] == 0:
                a[p] = self.new()
            p = a[p]
            self.c[p] += 1

    def remove(self, x):
        p = 1
        path = [1]
        bits = []

        for b in range(29, -1, -1):
            bit = (x >> b) & 1
            bits.append(bit)
            p = self.o[p] if bit else self.z[p]
            path.append(p)

        for p in path:
            self.c[p] -= 1

        for j in range(30, 0, -1):
            p = path[j]
            if self.c[p] > 0:
                break
            par = path[j - 1]
            if bits[j - 1]:
                self.o[par] = 0
            else:
                self.z[par] = 0
            self.free.append(p)

    def query(self, x):
        if self.c[1] == 0:
            return 0

        p = 1
        ans = 0

        for b in range(29, -1, -1):
            bit = (x >> b) & 1
            q = self.o[p] if bit == 0 else self.z[p]
            r = self.z[p] if bit == 0 else self.o[p]

            if q and self.c[q] > 0:
                ans |= (1 << b)
                p = q
            else:
                p = r

        return ans


def solve():
    input = sys.stdin.readline
    T = int(input())

    for _ in range(T):
        n = int(input())
        A = [x - 1 for x in map(int, input().split())]
        V = list(map(int, input().split()))

        # Find cycle nodes
        indeg = [0] * n
        for x in A:
            indeg[x] += 1

        q = deque(i for i in range(n) if indeg[i] == 0)

        while q:
            u = q.popleft()
            v = A[u]
            indeg[v] -= 1
            if indeg[v] == 0:
                q.append(v)

   
        rev = [[] for _ in range(n)]
        for i in range(n):
            if indeg[i] == 0:
                rev[A[i]].append(i)

        ans = [0] * n
        visited = [False] * n

       
        for start in range(n):
            if indeg[start] == 0 or visited[start]:
                continue

            cycle = []
            u = start

            while not visited[u]:
                visited[u] = True
                cycle.append(u)
                u = A[u]

            k = len(cycle)

     
            P = [0] * (2 * k + 1)

            for j in range(1, 2 * k + 1):
                P[j] = P[j - 1] ^ V[cycle[(j - 1) % k]]

            total = P[k]

           
            ct = Trie()
            for j in range(2, k + 2):
                ct.insert(P[j])

           
            for s, root in enumerate(cycle):

                if s > 0:
                    ct.remove(P[s + 1])
                    ct.insert(P[s + k + 1])

                base = P[s + 1]

                tt = Trie()
                tt.insert(0)

                pref = {root: V[root]}
                stack = [(root, 0)]

                while stack:
                    u, state = stack.pop()

                    if state == 0:
                        x = pref[u]

                      
                        best = tt.query(x)

                        
                        target = x ^ base
                        cbest = max(
                            ct.query(target),
                            ct.query(target ^ total)
                        )

                        ans[u] = max(best, cbest)

                        tt.insert(x)
                        stack.append((u, 1))

                        for child in rev[u]:
                            pref[child] = x ^ V[child]
                            stack.append((child, 0))

                    else:
                        tt.remove(pref[u])

        print(*ans)


if __name__ == "__main__":
    solve()