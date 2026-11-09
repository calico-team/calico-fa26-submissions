import sys
def solution():
    test=sys.stdin.read()
    data=test.split()
    if not data:
        return
    life=int(data[0])
    index=1
    outcome=[]
    for i in range(life):
        lifee=int(data[index])
        index+=1
        mini=[int(x) for x in data[index:index+lifee]]
        index+=lifee
        maxi=[int(x) for x in data[index:index+lifee]]
        index+=lifee
        sumy=0
        for j in range(29,-1,-1):
            result=sum | (1<<j)
            possible=True
            for k in range(lifee):
                leastmaf=mini[k]
                mostmaf=maxi[k]
                if j<29:
                 mask=~((1<<j)-1)
                else:0
                if possible:
                   sumy=result
        outcome.append(str(sumy))
    print('\n'.join(outcome))
if __name__=='__main__':
    solution()
        
        
        