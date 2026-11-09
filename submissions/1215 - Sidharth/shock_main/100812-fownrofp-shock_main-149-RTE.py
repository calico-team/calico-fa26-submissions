"""
*Return an N by M grid displaying the reading of the block seismometers after all earthquakes occur.
*
*N: number of rows in the grid
*M: number of columns in the grid
*Q: number of earthquakes
*earthquakes: a list of tuples (X, Y, P), where:
*    X: column of the epicenter
*    Y: row of the epicenter
*    P: power of the earthquake
"""
import numpy as np
def solve(N, M, Q, earthquakes):
    # YOUR CODE HERE
    size = N*M
    logs = np.zeros(M+2, dtype=np.int64)
    for x in range(2, M+2):
        logs[x] = logs[x//2]+1
    
    levels= int(logs[M])+1
    table = np.full((levels,size+1),-1,dtype=np.int32)
    rows_list=[]
    cols_list=[]
    power_list=[]

    for i in range(Q):
        row=earthquakes[i][0]
        col=earthquakes[i][1]
        power = earthquakes[i][2]
        rows_list.append(row)
        cols_list.append(col)
        power_list.append(power)
        offsets = np.arange(-power, power +1)
        width = np.sqrt(power* power -offsets *offsets).astype(np.int64)
        length = 2*width+1
        k = logs[length]

        start = (row + offsets) * M + col - width
        end = (row + offsets)* M+ col+ width+ 1-(1 << k)
        table[k, start] =i
        table[k, end] =i

    for k in range(levels - 1, 0, -1):
        half = 1<<(k - 1)
        top = table[k]
        table[k-1]=np.maximum(table[k - 1],top)
        table[k-1, half:] = np.maximum(table[k -1, half:],top[:size +1- half])
    newest =table[0, :size].astype(np.int64)
    ans = np.zeros(size, dtype=np.int64)

    hit = np.nonzero(newest >= 0)[0]
    q = newest[hit]
    R = np.array(rows_list, dtype=np.int64)[q]
    C = np.array(cols_list, dtype=np.int64)[q]
    P = np.array(power_list, dtype=np.int64)[q]
    r = hit // M
    c = hit % M
    ans[hit] = P * P - ((r - R) * (r - R) + (c - C) * (c - C)) + 1

    return ans.reshape(N, M).tolist()

def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        earthquakes = []
        for i in range(Q):
            X, Y, P = map(int, input().split())
            earthquakes.append((X, Y, P))
        answer = solve(N, M, Q, earthquakes)
        for row in answer:
            print(' '.join(map(str, row)))

if __name__ == '__main__':
    main()