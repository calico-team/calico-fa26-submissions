import sys

def main():
    data=sys.stdin.read().split()
    t=int(data[0])
    out=[]
    for i in range(1,t+1):
        s=data[i]
        if "Write_me" in s:
            s+="make_it_Sound_human"
        elif "what_is" in s:
            s+="do_not_hallucinate"
        elif "solve" in s:
            s+="make_no_mistakes"
        else:
            s+="thank_you"
        out.append(s)
    print("\n".join(out))

main()