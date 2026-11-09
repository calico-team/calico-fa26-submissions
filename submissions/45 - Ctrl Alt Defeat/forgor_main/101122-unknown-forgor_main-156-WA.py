

from typing import Tuple, List

Parent, Child = int, int
Edge = Tuple[Parent, Child]
Tree = List[Edge]

def build_tree(arr: List[int], n) -> Tree:
    tree = []
    # count = [0] * n
    degree = [1] * n
    for i in arr:
        # count[i] += 1
        degree[i] += 1

    #first leaf
    ptr = 0
    while degree[ptr] != 1:
        ptr += 1
    leaf = ptr

    for char in arr:
        tree.append((leaf, char))

        degree[leaf] -= 1

        if degree[char] == 1 and char < ptr:
            # new leaf candiddate that is smaller than the current leaf
            leaf = char
        else:
            ptr+=1
            while degree[ptr] != 1:
                ptr += 1
            leaf = ptr

    #finish up, add max root node
    tree.append((leaf, n-1))

    return tree


def build_prufer(tree: Tree, n: int) -> List[int]:
    '''
    Converts a tree to its respective Prüfer sequence.
    '''
    degree = [0] * n
    adj = [[] for _ in range(n)]
    for parent, child in tree:
        adj[parent].append(child)
        adj[child].append(parent)
        degree[parent] += 1
        degree[child] += 1


    node_to_parent = [0] * n

    head = [n-1]
    visited = set([n-1])
    while head:
        node = head.pop()
        for next in adj[node]:
            if next not in visited:
                node_to_parent[next] = node
                visited.add(next)
                head.append(next)

    ptr = 0 #less than or equal to smallest indexed leaf
    prufer = []
    while ptr < n and len(prufer) < n-2:
        if degree[ptr] == 1:
            # case: ptr is a leaf node, this must be smallest due to invariant
            parent = node_to_parent[ptr]
            prufer.append(parent)

            degree[ptr] -= 1
            degree[parent] -= 1

            if degree[parent] == 1:
                #now parent is a leaf node candidate that didn't considered
                if parent > ptr:
                    # we move on, we may hit the parent again in the future as ptr increments, so no problem here
                    continue
                # in this case, the parent violate invariant, so we need to address immediately,
                # parent must be the next leaf node to be processed
                while parent < ptr and degree[parent] == 1 and len(prufer) < n-2:
                    next_parent = node_to_parent[parent]
                    prufer.append(next_parent)

                    degree[next_parent] -= 1
                    degree[parent] -= 1
                    parent = next_parent
        ptr += 1
    return prufer

from functools import reduce

def sum_modded(prufer, n):
    return reduce(lambda x, y: (x + y) % n, prufer)

def first_phase(n):
    tree = []
    for i,v in (map(int, input().strip().split()) for _ in range(n-1)):
        a = i-1
        b = v-1
        tree.append((a, b))
    prufer = build_prufer(tree, n)
    modded_sum = sum_modded(prufer, n)
    print(' '.join(str(i+1) for i in [modded_sum, modded_sum] + prufer))

def second_phase(n):
    array = list(map(lambda x: int(x), input().strip().split(' ')))
    prufer = [x-1 for x in array[2:]]
    negatived_index = array.index(-1)
    if negatived_index >= 2: #the negative index is in the prufer payload
        modded_sum = array[0]
        # sum of original prufer is sum_modded(prufer, n) = M
        # M = remaining + (-1) - recovered_value (mod n)
        # M - (-1) - remaining + negatived_index
        recovered_value = (modded_sum - sum_modded(prufer, n) + 1) % n
        prufer[negatived_index-2] = recovered_value
    tree = build_tree(prufer, n)
    for edge in tree:
        print(edge[0]+1, edge[1]+1)
phase = input().strip()
if phase == "FIRST":
    first_phase(int(input().strip()))
elif phase == "SECOND":
    second_phase(int(input().strip()))
