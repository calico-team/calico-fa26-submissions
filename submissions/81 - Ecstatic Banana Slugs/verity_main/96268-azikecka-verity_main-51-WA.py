import sys
def crsofclen(char,length):
    ret = []
    for i in range(length):
        ret.append(char)
    return "".join(ret)
p = int(input())
for z in range(p):
    yay = False
    d1 = input().split()
    length = int(d1[0])
    nites = int(d1[1])
    ites = input().split()
    array = []
    for i in range(length):
        array.append("_")
    for i in range(nites):
        print(crsofclen(ites[i],length))
        sys.stdout.flush()
        cor = input()
        anscor = list(cor)
        if cor == "CORRECT":
            print(crsofclen(ites[i],length))
            yay = True
            break
        for j in range(length):
            
            if anscor[j] != "_":
                array[j] = anscor[j]
    if yay == True:
        continue
    print("".join(array))
    sys.stdout.flush()
    input()

