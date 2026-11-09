def solve(N,R,A):

    charges = 2
    ready = 0
    for t in A:
        while charges <2 and ready <= t:
            charges += 1
            if charges < 2: 
             ready += R
        if charges == 0:
            return "NO"
        if charges == 2:
            ready = t + R
        charges -= 1
    return "YES"

def main():
    T = int(input())
    for _ in range(T):
        temp = input().split()
        N = int(temp[0])
        R = int(temp[1])
        A = list(map(int, input().split()))
        print(solve(N,R,A))

if __name__ == '__main__':        
    main()