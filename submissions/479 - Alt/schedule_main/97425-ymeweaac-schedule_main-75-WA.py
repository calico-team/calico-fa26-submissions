import sys

def problem6():
    raw_input = sys.stdin.read().split()
    if not raw_input:
        return
    
    iterator = iter(raw_input)
    num_tests = int(next(iterator))
    
    for _ in range(num_tests):
        total_courses = int(next(iterator))
        max_semesters = int(next(iterator))
        limit_per_sem = int(next(iterator))
        
        prereq_count = [0] * (total_courses + 1)
        children = [[] for _ in range(total_courses + 1)]
        
        for course_id in range(1, total_courses + 1):
            parent = int(next(iterator))
            if parent != 0:
                children[parent].append(course_id)
                prereq_count[course_id] += 1
                
        eligible_courses = []
        for course_id in range(1, total_courses + 1):
            if prereq_count[course_id] == 0:
                eligible_courses.append(course_id)
                
        completed_count = 0
        
        for semester in range(max_semesters):
            if not eligible_courses:
                break
                
            batch_size = min(limit_per_sem, len(eligible_courses))
            current_batch = eligible_courses[:batch_size]
            eligible_courses = eligible_courses[batch_size:]
            
            completed_count += batch_size
            newly_unlocked = []
            
            for course in current_batch:
                for dependent in children[course]:
                    prereq_count[dependent] -= 1
                    if prereq_count[dependent] == 0:
                        newly_unlocked.append(dependent)
                        
            eligible_courses.extend(newly_unlocked)
            
        print(completed_count)

if __name__ == '__main__':
    problem6()
