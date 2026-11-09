test_count = int(input())


def can_travel(start, end, map, w, h):

    travelled = set([])

    stack = [(start, "R"), (start, "B")]

    while stack:
        
        state = stack.pop()
        if state in travelled:
            continue
        else:
            travelled.add(state)

        pos = state[0]
        if (pos == end):
            return True
        type_ = state[1]

        x = pos[0]
        y = pos[1]

        if x-1 >= 0 and map[y][x-1] in {type_, "."} and ((x-1, y), type_) not in travelled:
            stack.append(((x-1, y), type_))

        if x+1 < w and map[y][x+1] in {type_, "."} and ((x+1, y), type_) not in travelled:
            stack.append(((x+1, y), type_))

        if y-1 >= 0 and map[y-1][x] in {type_, "."} and ((x, y-1), type_) not in travelled:
            stack.append(((x, y-1), type_))

        if y+1 < h and map[y+1][x] in {type_, "."} and ((x, y+1), type_) not in travelled:
            stack.append(((x, y+1), type_))

        if map[y][x] == ".":
            if (pos, "R") not in travelled:
                stack.append((pos, "R"))
            if (pos, "B") not in travelled:
                stack.append((pos, "B"))

    return False




for i in range(test_count):
    map = []
    items = input().split()
    h = int(items[0])
    w = int(items[1])
    queries_count = items[2]
    for j in range(h):
        map.append(input())

    

    for q in range(int(queries_count)):
        pos = input().split()
        start = int(pos[1]), int(pos[0])
        end = int(pos[3]), int(pos[2])
        if can_travel(start, end, map, w, h): print("YES")
        else: print("NO")


      
# YES
# YES
# NO
# YES
# YES
# YES
# YES


