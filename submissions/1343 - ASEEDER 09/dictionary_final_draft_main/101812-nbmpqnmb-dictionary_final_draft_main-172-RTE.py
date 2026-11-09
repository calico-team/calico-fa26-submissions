N =int(input(""))
A =[1,2,3,4.5]
V =[1,5,7,3,6]
max =A[0]
fast =V[0]
for N in range(5):
    if  A[N] >max:
        max =A[N]
    if V[N] >fast:
        fast =V[N]
print(fast)
print(max)
