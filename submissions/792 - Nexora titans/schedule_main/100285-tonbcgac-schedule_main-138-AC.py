import sys
import heapq


def main():
    tokens = sys.stdin.read().split()
    idx = 0
    num_tests = int(tokens[idx]); idx += 1
    answers = []

    for _ in range(num_tests):
        num_courses = int(tokens[idx])
        num_semesters = int(tokens[idx + 1])
        per_semester = int(tokens[idx + 2])
        idx += 3
        prereq = [0] * (num_courses + 1)
        dependents = [[] for _ in range(num_courses + 1)]
        for course in range(1, num_courses + 1):
            prereq_id = int(tokens[idx]); idx += 1
            prereq[course] = prereq_id
            dependents[prereq_id].append(course)

        topo_order = []
        bfs_queue = list(dependents[0])
        front = 0
        while front < len(bfs_queue):
            course = bfs_queue[front]; front += 1
            topo_order.append(course)
            bfs_queue.extend(dependents[course])

        chain_len = [1] * (num_courses + 1)
        for course in reversed(topo_order):
            prereq_id = prereq[course]
            if prereq_id != 0 and chain_len[course] + 1 > chain_len[prereq_id]:
                chain_len[prereq_id] = chain_len[course] + 1

        available = [(-chain_len[course], course) for course in dependents[0]]
        heapq.heapify(available)
        total_taken = 0
        for _ in range(num_semesters):
            if not available:
                break
            picked = []
            while available and len(picked) < per_semester:
                picked.append(heapq.heappop(available)[1])
            total_taken += len(picked)
            for course in picked:
                for child in dependents[course]:
                    heapq.heappush(available, (-chain_len[child], child))

        answers.append(str(total_taken))

    sys.stdout.write("\n".join(answers) + "\n")


if __name__ == "__main__":
    main()