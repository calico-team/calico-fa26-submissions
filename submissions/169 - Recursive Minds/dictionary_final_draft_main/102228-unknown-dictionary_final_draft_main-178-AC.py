from array import array

def solve(N: int, A: list[int], V: list[int]) -> list[int]:
    A = [(x - 1) for x in A]
    bachay = [[] for _ in range(N)]
    for i in range(N):
        bachay[A[i]].append(i)

    state = [0] * N
    on_cycle = [0] * N
    answer = [0] * N
    cycles = []

    for s in range(N):
        path = []
        u = s
        while state[u] == 0:
            state[u] = 1
            path.append(u)
            u = A[u]
        if state[u] == 1:
            c_e = path[path.index(u):]
            for x in c_e:
                on_cycle[x] = 1
            cycles.append(c_e)
        for x in path:
            state[x] = 2

    c_d = array('i', [0, 0])
    count = array('i', [0])

    def naya(v, c):
        node = 0
        count[0] += c
        for bit in range(29, -1, -1):
            k = 2 * node + ((v >> bit) & 1)
            if c_d[k] == 0:
                c_d[k] = len(count)
                c_d.append(0)
                c_d.append(0)
                count.append(0)
            node = c_d[k]
            count[node] += c

    def axha_xor(v):
        node, result = 0, 0
        for bit in range(29, -1, -1):
            k = 2 * node + 1 - ((v >> bit) & 1)
            n_t = c_d[k]
            if n_t and count[n_t] > 0:
                result += 1 << bit
                node = n_t
            else:
                node = c_d[k ^ 1]
        return result

    for c_e in cycles:
        p_x = []
        value = 0
        del c_d[2:]
        del count[1:]
        c_d[0] = c_d[1] = count[0] = 0
        for u in c_e:
            p_x.append(value)
            value ^= V[u]

        for p in p_x:
            naya(p, 1)
            naya(p ^ value, 1)

        for i, root in enumerate(c_e):
            stack = []
            answer[root] = axha_xor(p_x[i])
            for u in bachay[root]:
                if not on_cycle[u]:
                    stack.append((u, V[u] ^ p_x[i], 0))

            while stack:
                u, p, l = stack.pop()
                if l:
                    naya(p, -1)
                    continue
                answer[u] = axha_xor(p)
                naya(p, 1)
                stack.append((u, p, 1))
                for nxt in bachay[u]:
                    stack.append((nxt, p ^ V[nxt], 0))

    return answer

def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        A = list(map(int, input().split()))
        V = list(map(int, input().split()))
        print(' '.join(map(str, solve(N, A, V))))

if __name__ == '__main__':
    main()
