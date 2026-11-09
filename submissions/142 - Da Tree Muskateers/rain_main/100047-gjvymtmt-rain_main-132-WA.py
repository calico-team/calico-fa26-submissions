for i in range(int(input())):
    amount,days=map(int,input().split())
    east=dict()
    north=dict()
    final=amount*days
    for i in range(amount):
        inputs=input().split()
        if inputs.pop()=="E":
            east.update({i:[int(inputs[0]),int(inputs[1])]})
        else:
            north.update({i:[int(inputs[0]),int(inputs[1])]})
    for x in east:
        for y in north:
            if abs(east[x][0]-north[y][0])==abs(east[x][-1]-north[y][-1]):
                if abs(east[x][0]-north[y][0])<days:
                    final=final-1
    print(final)