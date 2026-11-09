# t=int(input())
# def case(i):
#     if 'write_me' in i:
#         i+='make_it_sound_human'
#     elif 'what_is' in i:
#             i+='do_not_hallucinate'
#     elif 'solve' in i:
#             i+='make_no_mistakes'
#     else:
#           i+='thank_you'
#     return i
# for _ in range(t):
#     print(case(input()))

# def solve(N, R, A):
#     smoke=2
#     for i in range(N):    
#         if A[i]<=R and smoke<2:
#             smoke+=1
#     return 'YES' if smoke<=3 else 'NO'


# def main():
#     T = int(input())
#     for _ in range(T):
#         temp = input().split()
#         N = int(temp[0])
#         R = int(temp[1])
#         A = list(map(int, input().split()))
#         print(solve(N, R, A))


# if __name__ == '__main__':
#     main()

"""
* Return an integer denoting the amount of rain collected after the Kth nights 
*
* N: Number of drones
* K: Number of nights
* L: a list in this order [X, Y, Z, D] for each drone
*   X: Starting X location of Drone
*   Y: Starting Y location of Drone
*   Z: Starting Z location of Drone
*   D: Starting direction of Drone
"""
dir={'N':(0,1),'E':(1,0),'S':(0,-1),'W':(-1,0)}
def move_drone(X,Y,Z,D):
    movex,move_y=dir[D] #directions from dictionary top
    return (X+movex,Y+move_y,Z,D)
def is_covered(X,Y,Z,L):
    for other_X,other_Y,other_Z,other_D in L:
        if other_X==X and other_Y==Y and other_Z>Z:
            return True
    return False
def solve(N: int, K: int, L: list):
    rain_collected=0
    for _ in range(K):
        for X,Y,Z,D in L:
            if not is_covered(X,Y,Z,L):
                rain_collected+=1
        for i in range(N): #move
            L[i]=move_drone(*L[i]) #unpack
    return rain_collected

def main():
    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        L = []
        for _ in range(N):
            X, Y, Z, D = input().split()
            L.append((int(X), int(Y), int(Z), D))

        print(solve(N, K, L))

if __name__ == '__main__':
    main()