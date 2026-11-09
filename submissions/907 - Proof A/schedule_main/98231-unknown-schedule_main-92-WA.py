from collections import defaultdict, deque
import heapq


def do():
    n, m, k = map(int, input().split())
    parent_of = [0] + list(map(int, input().split()))
    child_of = defaultdict(list)
    depth_of = defaultdict(int)
    height_of = defaultdict(int)
    for i in range(1, n+1):
        child_of[parent_of[i]].append(i)
    
    def calc_depth(i, h):
        height_of[i] = h
        if len(child_of[i]) == 0:
            depth_of[i] = 1
        else:
            depth_of[i] = sum(calc_depth(x, h+1) for x in child_of[i])+1
            # for x in child_of[i]:
            #     calc_depth(x, h+1)
            # depth_of[i] = len(child_of[i])
        return depth_of[i]
    calc_depth(0, 0)
    kys = list(child_of.keys())
    for i in kys:
        child_of[i].sort(key = lambda x: (-depth_of[i], height_of[i])) 
    node_order = []
    q = [(-depth_of[0], height_of[0], 0)]
    heapq.heapify(q)
    while len(q):
        d, h, top = heapq.heappop(q)
        node_order.append(top)
        for x in child_of[top]:
            heapq.heappush(q, (-depth_of[x], height_of[x], x))
    # print(node_order)
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



