test_count = int(input())


def travel(start, map, w, h):

    #print("call")

    travelled = set([])
    all_pos = set([])

    stack = [(start, "R")]

    while stack:
        
        state = stack.pop()
        if state in travelled:
            continue
        else:
            travelled.add(state)
        

        pos = state[0]
        all_pos.add(pos)
        
        type_ = state[1]

        y = pos[0]
        x = pos[1]

        if map[y][x] == ".":
            if (pos, "R") not in travelled:
                stack.append((pos, "R"))
            if (pos, "B") not in travelled:
                stack.append((pos, "B"))

        if x-1 >= 0 and map[y][x-1] in {type_, "."} and ((y, x-1), type_) not in travelled:
            stack.append(((y, x-1), type_))

        if y-1 >= 0 and map[y-1][x] in {type_, "."} and ((y-1, x), type_) not in travelled:
            stack.append(((y-1, x), type_))

        if x+1 < w and map[y][x+1] in {type_, "."} and ((y, x+1), type_) not in travelled:
            stack.append(((y, x+1), type_))

        if y+1 < h and map[y+1][x] in {type_, "."} and ((y+1, x), type_) not in travelled:
            stack.append(((y+1, x), type_))

        #print(stack)
            

    return all_pos




for i in range(test_count):
    map = []
    items = input().split()
    h = int(items[0])
    w = int(items[1])
    queries_count = items[2]
    for j in range(h):
        map.append(input())

    partitions = []

    for q in range(int(queries_count)):
        pos = input().split()
        start = int(pos[0]), int(pos[1])
        end = int(pos[2]), int(pos[3])

        #print(partitions)
        #print(start, end)

        can_travel = False
        stop = False
        for partition in partitions:
            if start in partition:
                if end in partition:
                    can_travel = True
                stop = True
            if end in partition:
                stop = True

        if not stop:
            partition = travel(start, map, w, h)
            if end in partition: 
                can_travel = True
            
            partitions.append(partition)
            #print(partitions)

        if can_travel: print("YES")
        else: print("NO")



        


      
# YES
# YES
# NO
# YES
# YES
# YES
# YES


