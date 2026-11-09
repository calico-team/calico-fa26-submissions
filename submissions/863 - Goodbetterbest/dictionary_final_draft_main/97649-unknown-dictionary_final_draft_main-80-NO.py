import sys
from array import array

BITS = 30
def trie_add(left,right,cnt,x,delta):
    node = 0

#for loop
    for b in range(BITS -1 , -1 , -1):
        bit = (x >> b) & 1

        if bit == 0:
            nxt = left[node]

            if nxt == 0:
                nxt = len(cnt)
                left[node] = nxt

                left.append(0)
                right.append(0)
                cnt.append(0)

            else:
                nxt = right[node]

                if nxt == 0:
                    nxt = len(cnt)
                    right[node] = nxt
                    left.append(0)
                    right.append(0)
                    cnt.append(0)

            node = nxt
            cnt[node] += delta

def trie_query(left, right , cnt , x):
    node = 0
    result = 0

    for b  in range(BITS -1 , -1 , -1):
        bit = (x >> b) & 1
        want = bit ^ 1

        if want == 0:
            nxt = left[node]
        else:
            nxt = right[node]

        if nxt != 0 and cnt[nxt] >0:
            result |= ( 1<< b)
            node = nxt
        else:
            if bit == 0:
                node = left[node]
            else:
                node = right[node]

    return result

def solve():
    data = iter(map(int , sys.stdin.buffer.read().split()))

    T = next(data)
    output = []

    for _ in range(T):

        N = next(data)

        A = [next(data) -1 for _ in range(N)]
        V = [next(data) for _ in range(N)]

        #calculate indegree

        indeg = [0] * N

        for  u in range(N):
            indeg[A[u]]+= 1

        #remove nonn-cycle nodes
        queue = [
            u for u in range(N)
            if indeg[u] == 0
        ]

        head = 0

        while head < len(queue):
            u = queue[head]
            head += 1

            v = A[u]
            indeg[v] -= 1

            if indeg[v] == 0:
                queue.append(v)
     # remianing node are cycle node
        is_cycle = bytearray(
            1 if x > 0 else 0 for x in indeg
        )

        #build reverse tree 
        children = [[] for _ in range(N)]

        for u in range(N):
            if not is_cycle[u]:
                children[A[u]].append(u)
        ans = [0] *N
        seen = bytearray(N)

        #cycle trie
        leftB = array('i', [0])
        rightB = array('i', [0])
        cntB = array('i', [0])

        #path trie
        leftP = array('i' , [0])
        rightP = array('i' , [0])
        cntP = array('i' , [0])

        #find every cycle
        for s in range(N):
            if not is_cycle[s]  or seen[s]:
                continue
            cyc = []
            u = s

            while not seen[u]:
                seen[u] = 1
                cyc.append(u)
                u =A[u]

            L = len(cyc)
            # calculate cycle prefix XOR
            pref = [0] * (L + 1)

            for i in range(L):
                pref[i +1] = pref[i] ^ V[cyc[i]]

            C = pref[L]

            #reset and build cycle tire
            leftB.clear()
            rightB.clear()
            cntB.clear()

            leftB.append(0)
            rightB.append(0)
            cntB.append(0)

            for i in range(L):
                trie_add(
                    leftB , rightB, cntB,
                    pref[i],1
                )
                trie_add(
                    leftB , rightB, cntB,
                    pref[i] ^ C,1
                )

            # process each cycle root
            for j in range(L):
                root = cyc[j]
                shift = pref[ j+ 1]

                #reset path trie
                leftP.clear()
                rightP.clear()
                cntP.clear()

                leftP.append(0)
                rightP.append(0)
                cntP.append(0)

                trie_add(
                    leftP, rightP, cntP,0,1
                )

                stack = [(root , V[root], 0)]

                while stack:
                    u, q , state = stack.pop()

                    if state == 1:
                        trie_add(
                            leftP, rightP, cntP,q,-1
                        )
                        continue

                    x = trie_query(
                        leftP , rightP , cntP, q
                    )

                    y = trie_query(
                        leftB , rightB , cntB, q ^ shift
                    )

                    ans[u] = max(x , y)

                    trie_add(
                        leftP, rightP, cntP, q ,1
                    )
                    stack.append((u , q ,1))

                    for v in children[u]:
                        stack.append((
                            v,
                            q ^ V[v],
                            0
                        ))   

        output.append("".join(map(str , ans)))

    sys.stdout.write("\n".join(output))

if __name__ == " __main__":
    solve()          




                
