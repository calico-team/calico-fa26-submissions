def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]], K: list[int]) -> list[str]:
    """
    Return an array of Q strings, the i-th of which is "YES"
    if Big Ben can travel from start[i] to end[i] within K[i]
    seconds, and "NO" otherwise.

    N: the number of rows in the grid
    M: the number of columns in the grid
    Q: the number of queries
    G: the grid, where each tile is 'R', 'B', or '.'
    start: the (row, column) of the starting tile of each query
    end: the (row, column) of the ending tile of each query
    K: the maximum number of seconds allowed for each query
    """


    ansi = [10**18] * Q

    def bfs(graph,st):
        dist = [-1]*len(graph)
        queue =[st]
        dist[st] =0
        i = 0

        while i<len(queue):
            u= queue[i]
            i =i+1

            for v in graph[u]:
                if dist[v] ==-1:
                    dist[v] =dist[u] + 1
                    queue.append(v)

        return dist

    def eshem_check(left, right, ids):

        if len(ids)== 0 :
            return

        mid = (left+right)//2
        w = right - left + 1

        total = N *w * 2

        graph = [[] for _ in range(total)]

        for r in range(N):
            for c in range(w):

                caleshemcol = left + c
                ch = G[r][caleshemcol]

                for ecalmode in range(2):

                    u = (r * w + c) * 2 + ecalmode

                    if ch == ".":
                        v = u ^ 1
                        graph[u].append(v)
                        

                    if ch == "." or ( ch =="B" and ecalmode== 0) or (ch =="R" and ecalmode == 1):

                        if r > 0:
                            ch2 = G[r - 1][caleshemcol]

                            if ch2=="." or (ch2=="B" and ecalmode ==0) or (ch2 =="R" and ecalmode== 1):
                                v = ((r - 1) * w + c) * 2 + ecalmode
                                graph[u].append(v)
                                

                        if r < N - 1:
                            ch2 = G[r + 1][caleshemcol]

                            if ch2 == "." or (ch2 == "B" and ecalmode== 0) or (ch2 =="R" and ecalmode== 1):
                                v = ((r + 1) * w + c) * 2 + ecalmode
                                graph[u].append(v)
                                

                        if c >0:
                            ch2= G[r][caleshemcol - 1]

                            if ch2=="." or (ch2 ==  "B" and ecalmode==0) or (ch2 =="R" and ecalmode==1):
                                v = (r * w + c - 1) * 2 + ecalmode
                                graph[u].append(v)
                                

                        if c < w - 1 :
                            ch2 = G[r][caleshemcol +  1]

                            if ch2 == "." or (ch2=="B" and ecalmode==   0) or (ch2 ==  "R" and ecalmode==1):
                                v = (r * w + c + 1) * 2 + ecalmode
                                graph[u].append(v)
                                

        eshdatA=[]
        
        
        qeshleft=[]
        
        qeshemright=[]

        for qi in ids:

            sr,sc =start[qi]
            er,ec= end[qi]

            s=(sr * w+sc -left) *2
            e=(er*w +ec -left) *2

            eshdatA.append((qi, s, e, e + 1))

            if sc < mid and ec< mid:
                qeshleft.append(qi)

            elif sc>mid and ec> mid:
                qeshemright.append(qi)

        for r in range(N):
            for mode in range(2) :

                st=(r*w + mid - left)*2 + mode

                d=bfs( graph, st)

                for qi,s,e1,e2 in eshdatA:

                    a=d[s]

                    if a== -1:
                        continue

                    b=d[e1]
                    c=d[e2]

                    if b==-1:
                        b= 1000000000

                    if c==-1:
                        c =1000000000

                    value =a+min(b, c)

                    if value<ansi[qi]:
                        ansi[qi]=value

        if left<mid :
            eshem_check(left, mid - 1, qeshleft)

        if mid < right  :
            eshem_check(mid + 1, right, qeshemright)

    eshem_check(0, M - 1, list(range(Q)))

    result = []

    for i in range(Q):

        if ansi[i] <= K[i]:
            result.append("YES")
        else:
            result.append("NO")

    return result


def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        G = []
        for _ in range(N):
            G.append(input())
        start, end, K = [], [], []
        for _ in range(Q):
            start_row, start_col, end_row, end_col, k = map(int, input().split())
            start.append((start_row, start_col))
            end.append((end_row, end_col))
            K.append(k)
        for s in solve(N, M, Q, G, start, end, K):
            print(s)

if __name__ == '__main__':
    main()
