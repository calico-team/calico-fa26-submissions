import sys
def crsofclen(char,length):
    ret = []
    for i in range(length):
        ret.append(char)
    return "".join(ret)
p = int(input())
for z in range(p):
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
        anscor = list(input())
        for j in range(length):
            if anscor[j] != "_":
                array[j] = anscor[j]
    print("".join(array))
    sys.stdout.flush()
    input()

