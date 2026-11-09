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
    i = 0
    for _ in range(n-2):
        while ec[i] != 1:
            i += 1
        ed = tree[i].pop()
        tree[ed].remove(i)
        ec[i] -= 1
        ec[ed] -= 1
        r.append(ed)
        if ed < i and ec[ed] == 1:
            i = ed
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
    for i in range(n-2):
        for j in range(n):
            if vs[j] == 0:
                print(j+1, r[i]+1)
                vs[j] = -1
                vs[r[i]] -= 1
                break
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
