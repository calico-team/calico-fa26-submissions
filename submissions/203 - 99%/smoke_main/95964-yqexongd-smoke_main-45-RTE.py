def main(n, r):
    charges = 2
    uses = []
    u_index = 0
    reload = []
    r_index = 0
    for i in range(n):
        uses.append(int(input()))
    uses.sort()

    current_type = 'u'

    for j in range(2*n):
        if(current_type == 'u'):
            charges -= 1
            u_index += 1
        if(current_type == 'r'):
            charges += 1
            r_index += 1
        else:
            u_index += 1
            r_index += 1
        if(charges < 0):
            return("NO")

        if(uses[u_index] < reload[r_index]):
            current_type = 'u'

        elif(uses[u_index] > reload[r_index]):
            current_type = 'r'
        else:
            current_type = 'b'
    return "YES"

num = int(input())
for i in range(num):
    n, r = input().split()
    main(int(n), int(r))
