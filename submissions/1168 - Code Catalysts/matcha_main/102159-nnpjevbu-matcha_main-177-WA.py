def solve(N: int, L: list[int], R: list[int]) -> int:

    states = [0] * N  
    ans = 0
    
    for b in range(29, -1, -1):
        num_0, num_1, flexible = [], [], []
        
        for i in range(N):
            state = states[i]
            li, ri = (L[i] >> b) & 1, (R[i] >> b) & 1
            
            if state == 0:
                if li == 0 and ri == 0: num_0.append(i)
                elif li == 1 and ri == 1: num_1.append(i)
                else: flexible.append(i)
            elif state == 1:
                if li == 0: flexible.append(i)
                else: num_1.append(i)
            elif state == 2:
                if ri == 0: num_0.append(i)
                else: flexible.append(i)
            else:
                flexible.append(i)
                
        x_bit = 1 if flexible else (len(num_1) % 2)
        
        choices = {}
        if flexible:
            for i in flexible:
                st = states[i]
                if st == 0: choices[i] = 0
                elif st == 1: choices[i] = 1
                elif st == 2: choices[i] = 0
                else: choices[i] = 0
            
            current_sum = (len(num_1) + sum(choices[i] for i in flexible)) % 2
            if current_sum != x_bit:
                first_i = flexible[0]
                choices[first_i] = 1 - choices[first_i]
        
        ans = (ans << 1) | x_bit
        
        for i in num_0:
            st = states[i]
            if st == 0: states[i] = 0
            elif st == 1: states[i] = 1
            elif st == 2: states[i] = 2
            else: states[i] = 3
                
        for i in num_1:
            st = states[i]
            if st == 0: states[i] = 0
            elif st == 1: states[i] = 1
            elif st == 2: states[i] = 2
            else: states[i] = 3
                
        for i in flexible:
            x = choices.get(i, 0)
            st = states[i]
            if st == 0:
                states[i] = 1 if x == 0 else 2
            elif st == 1:
                states[i] = 1 if x == 0 else 3
            elif st == 2:
                states[i] = 3 if x == 0 else 2
            else:
                states[i] = 3
                
    return ans
  

def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        L = list(map(int, input().split()))
        R = list(map(int, input().split()))
        print(solve(N, L, R))

if __name__ == '__main__':
    main()
