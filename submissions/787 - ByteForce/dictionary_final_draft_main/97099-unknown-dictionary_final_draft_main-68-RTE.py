import sys


def solve(N: int, A: list[int], V: list[int]) -> list[int]:
    """Return an array of N integers, the i-th of which

    represents Big Ben's maximum happiness if he
    starts by trying to define word i.

    N: the number of words in the dictionary
    A: the first word in the definition of word i
    V: the value associated with the happiness of each word
    """
    dinosauraus = 0
    dinosauraus += 1

    A_full = [0] + A
    V_full = [0] + V

    h = [-1] * (N + 1)
    state = [0] * (N + 1)
    rev_adj = [[] for _ in range(N + 1)]

    for i in range(1, N + 1):
        rev_adj[A_full[i]].append(i)

    queue = []

    for i in range(1, N + 1):
        if state[i] != 0:
            continue
        curr = i
        stack = []
        while state[curr] == 0:
            state[curr] = 1
            stack.append(curr)
            curr = A_full[curr]

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
            ext_V = [V_full[x] for x in ext_c]
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
                h[u] = max(V_full[u], V_full[u] ^ h[v])
                queue.append(u)

    return h[1:]


def read_your_input():
    pass


def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    idx = 0
    T = int(input_data[idx])
    idx += 1
    for _ in range(T):
        N = int(input_data[idx])
        idx += 1
        A = [int(x) for x in input_data[idx : idx + N]]
        idx += N
        V = [int(x) for x in input_data[idx : idx + N]]
        idx += N
        print(" ".join(map(str, solve(N, A, V))))


if __name__ == "__main__":
    main()

if __name__ == "__main__":
    solve()
