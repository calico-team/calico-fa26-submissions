

from typing import Tuple, List

Parent, Child = int, int
Edge = Tuple[Parent, Child]
Tree = List[Edge]

# def build_tree(arr: List[int], n) -> Tree:
#     # https://en.wikipedia.org/wiki/Pr%C3%BCfer_sequence
#     tree = []
#     degree = [1] * n
#     for i in arr:
#         degree[i] += 1

#     for i in arr:
#         for node in range(n):
#             tree.append()

# // Source - https://stackoverflow.com/a/70139512
# // Posted by Sandipan Dey, modified by community. See post 'Timeline' for change history
# // Retrieved 2026-11-08, License - CC BY-SA 4.0

def get_tree(S):
    n = len(S)
    L = set(range(0, n+2))
    tree_edges = []
    for i in range(n):
        u, v = S[0], min(L - set(S))
        S.pop(0)
        L.remove(v)
        tree_edges.append((u,v))
    tree_edges.append((L.pop(), L.pop()))
    return tree_edges


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

def first_phase(n):
    tree = []
    for i,v in (map(int, input().strip().split()) for _ in range(n-1)):
        a = i-1
        b = v-1
        tree.append((a, b))
    prufer = [0,0] + build_prufer(tree, n)
    print(' '.join(str(i+1) for i in prufer))



def second_phase(n):
    prufer = list(map(lambda x: abs(int(x))-1, input().strip().split(' ')))[2:]
    tree = get_tree(prufer)
    for edge in tree:
        print(edge[0]+1, edge[1]+1)
phase = input().strip()
if phase == "FIRST":
    first_phase(int(input().strip()))
elif phase == "SECOND":
    second_phase(int(input().strip()))
