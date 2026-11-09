#!/usr/bin/env python3

tree = []
ec = []

def add_edge(a, b):
    global tree, ec
    tree[a].add(b)
    tree[b].add(a)
    ec[b] += 1
    ec[a] += 1

def phase1():
    global tree, ec
    n = int(input())
    tree = [set() for _ in range(n)]
    ec = [0 for _ in range(n)]
    for _ in range(n-1):
        a, b = [int(n) for n in input().split()]
        add_edge(a-1, b-1)
    r = []
    p = 0
    while ec[p] != 1:
        p += 1
    j = p
    for _ in range(n - 2):
        ed = tree[j].pop()
        tree[ed].remove(j)
        ec[j] -= 1
        ec[ed] -= 1
        r.append(ed)
        if ec[ed] == 1 and ed < p:
            j = ed
        else:
            p += 1
            while ec[p] != 1:
                p += 1
            j = p
    ra, rb = 0, 0
    for k in r:
        ra += k
        rb += ra // 1000000
        ra %= 1000000
    r.append(ra)
    r.append(rb)
    print(" ".join([str(n) for n in r]))


def phase2():
    n = int(input())
    vs = [0] * n
    ns = [int(n) for n in input().split()]
    ra = ns[-2]
    rb = ns[-1]
    if ra != -1 and rb != -1:
        missed = -1
        r = []
        for i in range(n-2):
            if ns[i] == -1:
                missed = i
            else:
                ra -= ns[i]
                if ra < 0:
                    ra += 1000000
                    rb -= 1
        ns[missed] = ra
    r = ns[:-2]
    for i in range(n-2):
        vs[r[i]] += 1
    p = 0
    while vs[p] != 0:
        p += 1
    j = p
    for i in range(n-2):
        print(j+1, r[i]+1)
        vs[j] = -1
        vs[r[i]] -= 1
        if vs[r[i]] == 0 and r[i] < p:
            j = r[i]
        else:
            p += 1
            while vs[p] != 0:
                p += 1
            j = p
    rem = []
    for i in range(n):
        if vs[i] == 0:
            rem.append(i)
    print(rem[0]+1, rem[1]+1)

p = input()
if p == "FIRST":
    phase1()
else:
    phase2()
