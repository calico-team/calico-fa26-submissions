import sys
def main():
    data = sys.stdin.read().split()
    pos = 0
    t = int(data[pos]);pos +=1
    output=[]
    for _ in range (t):
        n = int(data[pos]); m = int(data[pos+1]); q=int(data[pos+2]);pos +=3
        grid=[]
        for i in range(n):
            grid.append(data[pos]); pos +=1
        total=n*m
        parent =list(range(2*total))
        def find(x):
            while parent[x] !=x:
                parent[x] = parent[parent[x]]
                x = parent[x]
            return x
        def join_together(a,b):
            a = find(a)
            b=find(b)
            if a != b:
                parent[a]=b
        for r in range(n):
            for c in range(m):
                ch = grid[r][c]
                cell = r*m+c
                if ch == '.':
                    join_together(cell,cell+total)
                for mode in range(2):
                    my_color = 'B' if mode == 0 else 'R'
                    if ch != '.' and ch != my_color:
                        continue
                    if c+1<m:
                        nxt = grid[r][c+1]
                        if nxt == '.' or nxt == my_color:
                            join_together(cell+mode*total, cell+1+mode*total)
                    if r+1<n:
                        nxt = grid[r+1][c]
                        if nxt=='.' or nxt== my_color:
                            join_together(cell+mode*total,cell+m+mode*total)
        for _ in range(q):
            r1 = int(data[pos]);c1= int(data[pos+1])
            r2 = int(data[pos+2]);c2=int(data[pos+3])
            pos +=4
            start =r1*m+c1
            e = r2*m+c2
            s=find(start)
            if find(e)== s or find(e+total)==s:
                output.append("YES")
            else:
                output.append("NO")
    print("\n".join(output))
main()
                       



        

          

    