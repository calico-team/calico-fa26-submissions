import sys
def prblm():
    take=sys.stdin.read
    data=take().split()
    if not data:
        return
    inteT=int(data[0])
    index=1
    output=[]
    for i in range(inteT):
        smoke_req=int(data[index])
        smoke_rech=int(data[index+1])
        index+=2
        space=[]
        for j in range(smoke_req):
            space.append(int(data[index+j]))
        index+=smoke_req
        charges=2
        lastchar=0
        possible=True
        for times in space:
            if charges<2:
                timedone=times-lastchar
                gain=timedone//smoke_rech
                if gain>0:
                    charges+=gain
                    if charges>=2:
                        charges=2
                        lastchar=times
                    else:
                        lastchar+=gain*smoke_rech
            if charges>0:
                if charges==2:
                    lastchar=times
                charges-=1
            else:
                possible=False
                break
        if possible:
            output.append("YES")
        else:
            output.append("NO")
    print('\n'.join(output))
if __name__=='__main__':
    prblm()
                    
                
                
            