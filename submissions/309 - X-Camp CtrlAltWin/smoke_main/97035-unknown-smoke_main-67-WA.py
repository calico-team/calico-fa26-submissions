# def func():
#     t = int(input())
#     lst = []
#     lst3 = []
#     for i in range(t):
#         lst2 = []
#         smokes = 2
#         N, R = map(int, input("").split())
#         x = int, input("").split()
#         lst2.append(x)
#         y = len(lst)
#         for j in range(y):
#             smokes = smokes-1
#             if lst2[i] + R > lst2[i+1]:
#                 print("NO")
            
#         print("YES")
# func()   


def func(nums, secs, arr):   
    for i in range(len(arr) - 1):
       # print(arr[i], arr[i +1], secs)
       if arr[i] + secs > arr[i + 1]:
           return "NO"
    return "YES"
    
t = int(input())
ans = []
for _ in range(t):
    nums, secs = map(int, input().split())
    arr = list(map(int, input().split()))
    ans.append(func(nums, secs, arr))

for a in ans:
    print(a)


        
    
    




    
