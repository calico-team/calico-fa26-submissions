def solve(N: int, A: list[int], V: list[int]) -> list[int]:
    """
    Return an array of N integers, the i-th of which
    represents Big Ben's maximum happiness if he
    starts by trying to define word i.

    N: the number of words in the dictionary
    A: the first word in the definition of word i
    V: the value associated with the happiness of each word
    """
    
    nxt = [a - 1 for a in A]
    width = 1 << max(1, max(V).bit_length())
    low_masks = []
    for bit in range(width.bit_length() - 1):
        size = 1 << bit
        block = (1 << size) - 1
        mask = 0
        for start in range(0, width, size * 2):
            mask |= block << start
        low_masks.append(mask)

    def xor_transform(states: int, value: int) -> int:
        for bit, mask in enumerate(low_masks):
            if value & (1 << bit):
                size = 1 << bit
                high = mask << size
                states = ((states & mask) << size) | ((states & high) >> size)
        return states

    indegree = [0] * N
    reverse = [[] for _ in range(N)]
    for i, target in enumerate(nxt):
        indegree[target] += 1
        reverse[target].append(i)

    queue = [i for i in range(N) if indegree[i] == 0]
    removed = []
    for node in queue:
        removed.append(node)
        target = nxt[node]
        indegree[target] -= 1
        if indegree[target] == 0:
            queue.append(target)

    states = [0] * N
    for start in range(N):
        if indegree[start] == 0:
            continue
        cycle = []
        node = start
        while True:
            cycle.append(node)
            node = nxt[node]
            if node == start:
                break

        prefix_values = []
        prefix = 0
        for node in cycle:
            prefix ^= V[node]
            prefix_values.append(prefix)
        cycle_xor = prefix
        cycle_states = sum(1 << value for value in prefix_values)
        if cycle_xor:
            cycle_states |= xor_transform(cycle_states, cycle_xor)
        else:
            cycle_states |= 1

        prefix_before = 0
        for i, node in enumerate(cycle):
            states[node] = xor_transform(cycle_states, prefix_before)
            prefix_before = prefix_values[i]

    for node in reversed(removed):
        states[node] = (1 << V[node]) | xor_transform(states[nxt[node]], V[node])

    return [state.bit_length() - 1 for state in states]

def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        A = list(map(int, input().split()))
        V = list(map(int, input().split()))
        print(' '.join(map(str, solve(N, A, V))))

if __name__ == '__main__':
    main()
