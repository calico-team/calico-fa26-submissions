import sys

def main():
    data = sys.stdin.buffer.read().split()
    pos =0
    T = int(data[pos]); pos +=1
    out = []
    for _ in range(T):
        n = int(data[pos]); r = int(data[pos+1]); pos +=2
        count =2
        nxt =0
        ok =True
        for i in range(pos, pos+n):
            x = int(data[i])
            while count < 2 and nxt <= x:
                count +=1
                if count < 2:
                    nxt +=r
            if count ==0:
                ok = False
                break
            if count == 2:
                nxt = x + r
            count -= 1
        pos += n
        out.append("YES" if ok else "NO")
    print("\n".join(out))

main()