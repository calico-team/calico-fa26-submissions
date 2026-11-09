# CALICO Fall '26 - Problem 11: A Matcha a Day
# Third sample test case
#
# Intervals:
# Day 1: [0, 1]
# Day 2: [1, 2]
# Day 3: [3, 4]
# Day 4: [5, 8]
#
# One optimal choice is 1, 2, 4, 8.
# Their XOR is 15.

chosen_flavors = [1, 2, 4, 8]

maximum_xor = 0
for flavor in chosen_flavors:
    maximum_xor ^= flavor

print(maximum_xor)  # Output: 15
