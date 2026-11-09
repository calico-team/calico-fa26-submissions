def query(s):
    print(s)

    return input()


for _ in range(int(input())):
    n,k = map(int,input().split(" "))


    alpha = list(map(str, input().split(" ")))


    flag = 0

    ans = ['_' for i in range(n)]


    for c in alpha:
        res = query(c * n)

        if(res == 'CORRECT'):
            flag = 1
            break


        for i in range(n):
            if(res[i] == '_'):
                continue

            ans[i] = c

    if(flag):
        continue
    query("".join(ans))

#LFCV