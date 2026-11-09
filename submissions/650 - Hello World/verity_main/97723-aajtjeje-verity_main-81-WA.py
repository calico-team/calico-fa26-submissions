def solve(N,K,A):
    result= ['_']* N
    
    for ch in A[:-1]:
        print(ch * N, flush=True)

        response = input().strip()
       
        if response== "CORRECT":
            return
        if response=="p-1":
             return
        for i in range(N):
            if response[i]!='_' :
                result[i] = response[i]

    last = A[-1]
    for i in range(N):
        if result[i] =='_':
             result[i] = last
    print(''.join(result), flush=True)
    
    response = input().strip()
    if response=="-1" :
        return
