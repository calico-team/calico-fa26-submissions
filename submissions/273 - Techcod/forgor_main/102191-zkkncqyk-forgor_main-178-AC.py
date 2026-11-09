import sys
import heapq
def encode(n, edges):
    graph= [[] for _ in range(n+ 1)]
    deg=[0] *(n + 1)    
    for u, v in edges:
        graph[u].append(v)
        graph[v].append(u)
        deg[u] +=1
        deg[v] +=1
        
    leaf_heap =[i for i in range(1, n+1) if deg[i]==1]
    heapq.heapify(leaf_heap)    
    prufer_cod=[]    
    for _ in range(n - 2):
        leaf = heapq.heappop(leaf_heap)        
        for neighbor in graph[leaf]:
            if deg[neighbor] > 0:
                break
                
        prufer_cod.append(neighbor)
        deg[leaf] = 0
        deg[neighbor] -= 1        
        if deg[neighbor] == 1:
            heapq.heappush(leaf_heap, neighbor)
            
    return prufer_cod

def decode(n, prufer_cod):
    deg = [1] * (n+1)    
    for x in prufer_cod:
        deg[x] += 1        
    leaf_heap = [i for i in range(1, n + 1) if deg[i] == 1]
    heapq.heapify(leaf_heap)    
    edges =[]
    for x in prufer_cod:
        leaf = heapq.heappop(leaf_heap)
        edges.append((leaf, x))       
        deg[leaf] -=1
        deg[x] -=1        
        if deg[x]==1:
            heapq.heappush(leaf_heap, x)
            
    u = heapq.heappop(leaf_heap)
    v = heapq.heappop(leaf_heap)
    edges.append((u, v))    
    return edges

def main():
    reader=sys.stdin.readline    
    phase=reader().strip()
    n = int(reader())    
    if phase=="FIRST":
        edges=[tuple(map(int, reader().split())) for _ in range(n - 1)]
        code= encode(n, edges)        
        checksum=0
        for x in code:
            checksum ^= x            
        result= code+[checksum, 0]
        print(*result)
    else:
        arr = list(map(int, reader().split()))
        missing_idx= arr.index(-1)        
        if missing_idx < n-2:
            val=arr[n-2]
            for i in range(n - 2):
                if i != missing_idx:
                    val ^=arr[i]
            arr[missing_idx] =val            
        code= arr[:n- 2]
        edges=decode(n, code)        
        for u, v in edges:
            print(u, v)

if __name__ == "__main__":
    main()