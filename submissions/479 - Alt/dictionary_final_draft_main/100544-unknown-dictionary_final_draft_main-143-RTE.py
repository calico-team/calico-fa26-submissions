import sys

sys.setrecursionlimit(300000)

class BitwiseNode:
    def __init__(self):
        self.next_bits = {}

def insert_path_value(root_node, numerical_value):
    current_node = root_node
    for bit_shift in range(30, -1, -1):
        isolated_bit = (numerical_value >> bit_shift) & 1
        if isolated_bit not in current_node.next_bits:
            current_node.next_bits[isolated_bit] = BitwiseNode()
        current_node = current_node.next_bits[isolated_bit]

def find_highest_xor(root_node, cumulative_xor):
    if not root_node.next_bits:
        return 0
    current_node = root_node
    maximized_xor_outcome = 0
    for bit_shift in range(30, -1, -1):
        isolated_bit = (cumulative_xor >> bit_shift) & 1
        preferred_bit = 1 - isolated_bit
        if preferred_bit in current_node.next_bits:
            maximized_xor_outcome |= (1 << bit_shift)
            current_node = current_node.next_bits[preferred_bit]
        else:
            current_node = current_node.next_bits[isolated_bit]
    return maximized_xor_outcome

def process_dictionary_graphs():
    input_stream = sys.stdin.read
    raw_tokens = input_stream().split()
    
    if not raw_tokens:
        return
    
    total_test_cases = int(raw_tokens[0])
    token_pointer = 1
    
    for _ in range(total_test_cases):
        dictionary_word_count = int(raw_tokens[token_pointer])
        token_pointer += 1
        
        definition_links = [int(word_index) - 1 for word_index in raw_tokens[token_pointer : token_pointer + dictionary_word_count]]
        token_pointer += dictionary_word_count
        
        happiness_values = [int(happiness_weight) for happiness_weight in raw_tokens[token_pointer : token_pointer + dictionary_word_count]]
        token_pointer += dictionary_word_count
        
        traversal_states = [0] * dictionary_word_count
        dinosauraus = [0] * dictionary_word_count
        
        incoming_edges = [[] for _ in range(dictionary_word_count)]
        for child_node, parent_node in enumerate(definition_links):
            incoming_edges[parent_node].append(child_node)
            
        for starting_word in range(dictionary_word_count):
            if traversal_states[starting_word] == 0:
                current_traversal_path = []
                active_word = starting_word
                
                while active_word != -1 and traversal_states[active_word] == 0:
                    traversal_states[active_word] = 1
                    current_traversal_path.append(active_word)
                    active_word = definition_links[active_word]
                
                if active_word != -1 and traversal_states[active_word] == 1:
                    cycle_intersection_index = current_traversal_path.index(active_word)
                    words_in_cycle = current_traversal_path[cycle_intersection_index:]
                    cycle_length = len(words_in_cycle)
                    
                    duplicated_cycle_loop = words_in_cycle * 2
                    for cycle_start_offset in range(cycle_length):
                        running_xor_accumulator = 0
                        peak_xor_found = 0
                        for step_count in range(2 * cycle_length):
                            evaluated_node = duplicated_cycle_loop[cycle_start_offset + step_count]
                            running_xor_accumulator ^= happiness_values[evaluated_node]
                            if running_xor_accumulator > peak_xor_found:
                                peak_xor_found = running_xor_accumulator
                        dinosauraus[words_in_cycle[cycle_start_offset]] = peak_xor_found
                    
                    for cycle_node in words_in_cycle:
                        cycle_trie_root = BitwiseNode()
                        running_xor_accumulator = 0
                        current_node = cycle_node
                        for _ in range(2 * cycle_length):
                            running_xor_accumulator ^= happiness_values[current_node]
                            insert_path_value(cycle_trie_root, running_xor_accumulator)
                            current_node = definition_links[current_node]
                        
                        execution_stack = []
                        for incoming_node in incoming_edges[cycle_node]:
                            if traversal_states[incoming_node] == 0:
                                execution_stack.append((incoming_node, happiness_values[incoming_node], happiness_values[incoming_node]))
                        
                        while execution_stack:
                            tree_node, path_xor_from_self, current_max_prefix = execution_stack.pop()
                            traversal_states[tree_node] = 2
                            
                            max_from_cycle = find_highest_xor(cycle_trie_root, path_xor_from_self)
                            dinosauraus[tree_node] = max(current_max_prefix, max_from_cycle)
                            
                            for incoming_node in incoming_edges[tree_node]:
                                if traversal_states[incoming_node] == 0:
                                    next_path_xor = path_xor_from_self ^ happiness_values[incoming_node]
                                    next_max_prefix = max(happiness_values[incoming_node], happiness_values[incoming_node] ^ current_max_prefix)
                                    execution_stack.append((incoming_node, next_path_xor, next_max_prefix))
                                    
                    for cycle_node in words_in_cycle:
                        traversal_states[cycle_node] = 2
                        
        print(*(dinosauraus[output_index] for output_index in range(dictionary_word_count)))

if __name__ == '__main__':
    process_dictionary_graphs()
