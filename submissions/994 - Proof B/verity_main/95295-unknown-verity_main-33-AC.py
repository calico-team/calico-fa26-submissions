def verity():
    N,K=[int(a) for a in input().split()]
    chars=input().split()
    correct=False
    current=list("_"*N)
    current_index=0
    while correct==False:
        for index in range(N):
            if current[index]=="_":
                current[index]=chars[current_index]
        current_index=current_index+1
        current_str=""
        for char in current:
            current_str=current_str+char
        print(current_str)
        current=list(input())
        if current==list("CORRECT"):
            correct=True
T=int(input())
for case in range(T):
    verity()
