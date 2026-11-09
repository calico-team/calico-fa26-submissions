from collections import defaultdict
from bisect import bisect_right
import sys
def main():
    input_data =sys.stdin.read().split()
    if not input_data:
        return
    
    iterator =iter(input_data)
    num_test_case= int(next(iterator))
    results=[]
    for _ in range(num_test_case):
        n = int(next(iterator))
        k = int(next(iterator))
        track_group =defaultdict(lambda: [[], []])        
        for _ in range(n):
            x =int(next(iterator))
            y =int(next(iterator))
            z =int(next(iterator)) 
            direction=next(iterator)            
            if direction== 'E':
                track_group[x+ y][0].append(x)
            else:
                track_group[x +y][1].append(x)
        
        total_blockedinstances = 0
        
        for east_list, north_list in track_group.values():
            north_list.sort()
            for x_coord in east_list:
                lower_b= bisect_right(north_list, x_coord)
                upper_b=bisect_right(north_list, x_coord + k- 1)                
                total_blockedinstances += (upper_b-lower_b)        
        total_rainwater =(n * k) -total_blockedinstances
        results.append(str(total_rainwater))        
    print('\n'.join(results))

if __name__ =='__main__':
    main()
