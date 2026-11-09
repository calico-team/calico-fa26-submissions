


test_count = int(input())

for i in range(test_count):
    courses_depths = []
    prereq_chains = {}

    items = input().split()
    course_count = int(items[0])
    course_per_sem = int(items[2])
    sem = int(items[1])

    courses = input().split()

    for i in range(len(courses)):
        prereq_chains[i+1] = int(courses[i])

    for j in range(len(courses)):
        depth = 0
        c = j+1
        while prereq_chains[c] != 0:
            c = prereq_chains[c]
            depth += 1
        courses_depths.append((j+1, depth))

    courses_depths = sorted(courses_depths, key = lambda courses_depths: courses_depths[1])

    total = 0

    for i in range(sem):
        curr_sem = sem-i
        sem_left = curr_sem-1
        
        #print(sem_left, sem)

        for j in range(course_per_sem):
            if courses_depths == []:
                break
            last = courses_depths.pop()
            while last[1] > sem_left:
                if courses_depths == []: break
                last = courses_depths.pop()
                continue

            for j in range(len(courses_depths)):
                if courses_depths[j][0] == prereq_chains[last[0]]:
                    # must take, shift to front
                    courses_depths.append(courses_depths.pop(j))
            


            total += 1
    print(total)



