import sys
from array import array


def solve(N: int, A: list[int], V: list[int]) -> list[int]:
    target = [x - 1 for x in A]

    incoming = [[] for _ in range(N)]
    in_deg = [0] * N



    for u in range(N):
        v = target[u]
        incoming[v].append(u)
        in_deg[v] += 1

    q = [i for i in range(N) if in_deg[i] == 0]
    head = 0


    while head < len(q):
        curr = q[head]
        head += 1
        nxt = target[curr]
        in_deg[nxt] -= 1
        if in_deg[nxt] == 0:
            q.append(nxt)

    in_loop = bytearray(1 if x > 0 else 0 for x in in_deg)

    visited = bytearray(N)

    acc_xor = [0] * N


    loop_prefix = [0] * N
    res = [0] * N

    max_bits = max(max(V).bit_length(), 1)

    def add_num(val, child0, child1, freq):
        idx = 0
        freq[0] += 1
        for b in range(max_bits - 1, -1, -1):
            if (val >> b) & 1:
                nxt_idx = child1[idx]
                if nxt_idx == 0:
                    nxt_idx = len(child0)
                    child1[idx] = nxt_idx
                    child0.append(0)
                    child1.append(0)
                    freq.append(0)
            else:
                nxt_idx = child0[idx]
                if nxt_idx == 0:
                    nxt_idx = len(child0)
                    child0[idx] = nxt_idx
                    child0.append(0)
                    child1.append(0)
                    freq.append(0)
            idx = nxt_idx
            freq[idx] += 1




    def remove_num(val, child0, child1, freq):
        idx = 0
        freq[0] -= 1
        for b in range(max_bits - 1, -1, -1):
            if (val >> b) & 1:
                idx = child1[idx]
            else:
                idx = child0[idx]
            freq[idx] -= 1










    def query_max(val, child0, child1, freq):
        idx = 0
        val_xor = 0
        for b in range(max_bits - 1, -1, -1):
            if (val >> b) & 1:
                branch = child0[idx]
                if branch and freq[branch] > 0:
                    val_xor |= 1 << b
                    idx = branch
                else:
                    idx = child1[idx]
            else:
                branch = child1[idx]
                if branch and freq[branch] > 0:
                    val_xor |= 1 << b
                    idx = branch
                else:
                    idx = child0[idx]
        return val_xor



    for src in range(N):

        if not in_loop[src] or visited[src]:

            continue

        loop_nodes = []

        curr = src

        while not visited[curr]:

            visited[curr] = 1
            loop_nodes.append(curr)
            curr = target[curr]

        pref_list = []
        running_xor = 0
        for u in loop_nodes:
            running_xor ^= V[u]
            pref_list.append(running_xor)
            loop_prefix[u] = running_xor

        loop_xor = running_xor

        child0 = array('i', [0])
        child1 = array('i', [0])
        freq = array('i', [0])



        for val in pref_list:
            add_num(val, child0, child1, freq)
            add_num(val ^ loop_xor, child0, child1, freq)




        for anchor in loop_nodes:
            acc_xor[anchor] = V[anchor]
            base_key = acc_xor[anchor] ^ loop_prefix[anchor]
            res[anchor] = query_max(base_key, child0, child1, freq)

            add_num(base_key, child0, child1, freq)

            dfs_stack = [c for c in incoming[anchor] if not in_loop[c]]




            while dfs_stack:
                item = dfs_stack.pop()
                if item < 0:
                    node = ~item
                    remove_num(acc_xor[node] ^ loop_prefix[anchor], child0, child1, freq)
                    continue

                node = item
                acc_xor[node] = V[node] ^ acc_xor[target[node]]
                k = acc_xor[node] ^ loop_prefix[anchor]
                res[node] = query_max(k, child0, child1, freq)



                add_num(k, child0, child1, freq)
                dfs_stack.append(~node)




                for c in incoming[node]:
                    if not in_loop[c]:
                        dfs_stack.append(c)




            remove_num(base_key, child0, child1, freq)

    return res


def main():
    lines = sys.stdin.read().split()
    if not lines:
        return
    ptr = 0
    T = int(lines[ptr])
    ptr += 1

    for _ in range(T):
        N = int(lines[ptr])
        ptr += 1
        A = [int(x) for x in lines[ptr : ptr + N]]
        ptr += N
        V = [int(x) for x in lines[ptr : ptr + N]]
        ptr += N

        ans = solve(N, A, V)
        sys.stdout.write(' '.join(map(str, ans)) + '\n')


if __name__ == '__main__':
    main()
