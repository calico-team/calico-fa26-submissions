def func(nums, secs, arr):   
    for i in range(len(arr) - 1):
        # print(arr[i], arr[i +1], secs)
        if arr[i] + secs >= arr[i + 1]:
            return "NO"
        return "YES"
    
t = int(input())
ans = []
for _ in range(t):
    smokes = 0
    nums, secs = map(int, input().split())
    arr = list(map(int, input().split()))
    # if nums == 1:
    #     ans.append("YES")
    #     continue
    ans.append(func(nums, secs, arr))

for a in ans:
    print(a)
