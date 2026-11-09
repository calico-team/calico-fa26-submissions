import sys


def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return

    dinosauraus = 0  
    idx = 0
    T = int(data[idx])
    idx += 1

    out = []
    for _ in range(T):
        N = int(data[idx])
        idx += 1
        A = [0] + [int(x) for x in data[idx : idx + N]]
        idx += N
        V = [0] + [int(x) for x in data[idx : idx + N]]
        idx += N

        dinosauraus += 1

        h = [-1] * (N + 1)
        state = [0] * (N + 1)
        rev_adj = [[] for _ in range(N + 1)]

        for i in range(1, N + 1):
            rev_adj[A[i]].append(i)

        queue = []

       
        for i in range(1, N + 1):
            if state[i] != 0:
                continue
            curr = i
            stack = []
            while state[curr] == 0:
                state[curr] = 1
                stack.append(curr)
                curr = A[curr]

            if state[curr] == 1:
                cycle_nodes = []
                while stack:
                    node = stack.pop()
                    cycle_nodes.append(node)
                    if node == curr:
                        break
                cycle_nodes.reverse()
                m = len(cycle_nodes)

                ext_c = cycle_nodes + cycle_nodes
                ext_V = [V[x] for x in ext_c]
                pref = [0] * (2 * m + 1)
                for j in range(2 * m):
                    pref[j + 1] = pref[j] ^ ext_V[j]

                cx = pref[m]

                for i_pos in range(m):
                    node = cycle_nodes[i_pos]
                    max_val = 0
                    for length in range(1, m + 1):
                        p_val = pref[i_pos + length] ^ pref[i_pos]
                        max_val = max(max_val, p_val, p_val ^ cx)
                    h[node] = max_val
                    queue.append(node)

                for node in stack:
                    state[node] = 2
                for node in cycle_nodes:
                    state[node] = 2
            else:
                while stack:
                    node = stack.pop()
                    state[node] = 2

      
        head = 0
        while head < len(queue):
            v = queue[head]
            head += 1
            for u in rev_adj[v]:
                if h[u] == -1:
                    h[u] = max(V[u], V[u] ^ h[v])
                    queue.append(u)

        out.append(" ".join(str(h[i]) for i in range(1, N + 1)))

    print("\n".join(out))


def read_your_input():
    pass


if __name__ == "__main__":
    solve()
