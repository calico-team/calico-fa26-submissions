from collections import defaultdict, deque
def do():
    n, m, k = map(int, input().split())
    parent_of = [0] + list(map(int, input().split()))
    child_of = defaultdict(list)
    for i in range(1, n+1):
        child_of[parent_of[i]].append(i)
    kys = list(child_of.keys())
    for i in kys:
        child_of[i].sort(key = lambda x: -len(child_of[x])) 
    node_order = []
    q = deque([0])
    while len(q):
        top = q.popleft()
        node_order.append(top)
        for x in child_of[top]:
            q.append(x)

    time_of = defaultdict(lambda x: -2)
    num_possible = 0
    time = 0
    time_of[0] = -1
    done_at_time = 0
    for i in range(1, len(node_order)):
        node = node_order[i]
        if time == time_of[parent_of[node]] or done_at_time == k:
            time += 1
            done_at_time = 0
        if time == m:
            break
        num_possible += 1
        time_of[node] = time
        done_at_time += 1
    print(num_possible)

t = int(input())
for i in range(t):
    do()



