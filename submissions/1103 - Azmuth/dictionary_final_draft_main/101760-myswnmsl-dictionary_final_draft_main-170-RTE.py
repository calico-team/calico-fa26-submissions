
import sys
from collections import deque
from array import array


BITS = 30


def solve(N: int, A: list[int], V: list[int]) -> list[int]:

    A = [number - 1 for number in A]

    incoming_count = [0] * N

    for number in A:
        incoming_count[number] += 1

    class_queue = deque()

    for student in range(N):
        if incoming_count[student] == 0:
            class_queue.append(student)

    worksheet_order = []

    # Remove students outside the number loops
    while class_queue:
        student = class_queue.popleft()
        worksheet_order.append(student)

        next_student = A[student]
        incoming_count[next_student] -= 1

        if incoming_count[next_student] == 0:
            class_queue.append(next_student)

    # Persistent binary trie
    lower_branch = array('i', [0])
    upper_branch = array('i', [0])

    def add_number(previous_tree, number):

        new_tree = len(lower_branch)

        lower_branch.append(lower_branch[previous_tree])
        upper_branch.append(upper_branch[previous_tree])

        old_node = previous_tree
        new_node = new_tree

        for bit_position in range(BITS - 1, -1, -1):

            if (number >> bit_position) & 1:
                old_child = upper_branch[old_node]
                new_child = len(lower_branch)

                lower_branch.append(lower_branch[old_child])
                upper_branch.append(upper_branch[old_child])

                upper_branch[new_node] = new_child

            else:
                old_child = lower_branch[old_node]
                new_child = len(lower_branch)

                lower_branch.append(lower_branch[old_child])
                upper_branch.append(upper_branch[old_child])

                lower_branch[new_node] = new_child

            old_node = old_child
            new_node = new_child

        return new_tree

    def max_xor_score(result_tree, math_mask):

        final_score = 0
        current_node = result_tree

        for bit_position in range(BITS - 1, -1, -1):

            current_bit = (math_mask >> bit_position) & 1

            if current_bit == 0:
                preferred = upper_branch[current_node]
                alternative = lower_branch[current_node]
            else:
                preferred = lower_branch[current_node]
                alternative = upper_branch[current_node]

            if preferred != 0:
                final_score |= 1 << bit_position
                current_node = preferred
            else:
                current_node = alternative

        return final_score

    result_tree = [0] * N
    math_mask = [0] * N
    final_marks = [0] * N

    checked_students = [False] * N

    # Process every cycle
    for first_student in range(N):

        if incoming_count[first_student] == 0:
            continue

        if checked_students[first_student]:
            continue

        number_loop = []
        current_student = first_student

        while not checked_students[current_student]:
            checked_students[current_student] = True
            number_loop.append(current_student)
            current_student = A[current_student]

        loop_size = len(number_loop)

        # Calculate prefix XOR values
        xor_sequence = [0] * loop_size
        running_xor = 0

        for position in range(loop_size):
            xor_sequence[position] = running_xor
            running_xor ^= V[number_loop[position]]

        cycle_xor = running_xor

        # Build one shared trie for this cycle
        cycle_tree = 0

        for position in range(loop_size):
            cycle_tree = add_number(
                cycle_tree,
                xor_sequence[position]
            )

            cycle_tree = add_number(
                cycle_tree,
                xor_sequence[position] ^ cycle_xor
            )

        # Calculate answers for cycle students
        for position in range(loop_size):

            student = number_loop[position]

            result_tree[student] = cycle_tree
            math_mask[student] = xor_sequence[position]

            final_marks[student] = max_xor_score(
                cycle_tree,
                math_mask[student]
            )

    # Process students outside cycles
    for student in reversed(worksheet_order):

        next_student = A[student]

        next_mask = math_mask[next_student]

        result_tree[student] = add_number(
            result_tree[next_student],
            next_mask
        )

        math_mask[student] = next_mask ^ V[student]

        final_marks[student] = max_xor_score(
            result_tree[student],
            math_mask[student]
        )

    return final_marks


def main():
    read_your_input()


def read_your_input():

    data = list(map(int, sys.stdin.buffer.read().split()))

    position = 0
    test_cases = data[position]
    position += 1

    answers = []

    for _ in range(test_cases):

        N = data[position]
        position += 1

        A = data[position:position + N]
        position += N

        V = data[position:position + N]
        position += N

        final_marks = solve(N, A, V)

        answers.append(' '.join(map(str, final_marks)))

    sys.stdout.write('\n'.join(answers))


if __name__ == '__main__':
    main()
