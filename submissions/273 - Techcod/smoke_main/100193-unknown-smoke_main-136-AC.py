from collections import deque
import sys
def main():
    input_data= sys.stdin.read().split()
    if not input_data:
        return
    
    iterator=iter(input_data)
    num_test_cases=int(next(iterator))    
    for _ in range(num_test_cases):
        n = int(next(iterator))
        cooldown =int(next(iterator))
        timestamps=[int(next(iterator)) for _ in range(n)]
        charges = 2
        recharge_que= deque()
        for time in timestamps:
            while recharge_que and recharge_que[0] <=time:
                recharge_que.popleft()
                charges +=1
            if charges== 0:
                print("NO")
                break
            charges-=1
            if recharge_que:
                recharge_que.append(recharge_que[-1]+ cooldown)
            else:
                recharge_que.append(time+cooldown)
        else:
            print("YES")

if __name__=="__main__":
    main()