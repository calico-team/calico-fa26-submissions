import sys
import warnings
import numpy as np


def read_all_ints():
    #saari integer values ko pehlllay read kryn gy
    
    raw = sys.stdin.buffer.read()
    try:
        with warnings.catch_warnings():
            warnings.simplefilter("ignore")
            data = np.fromstring(raw, dtype=np.int64, sep=' ')   # yeh sab se tezz zariya hia
    except Exception:
        data = np.array(raw.split(), dtype=np.int64)
    return data


def main():
    data = read_all_ints()
    T = int(data[0]); p = 1
    outt_val = []
    
    for _ in range(T):
        N = int(data[p]); R = int(data[p + 1]); p += 2
        a = data[p:p + N]; p += N

        #bari bari hum jobs ko run kr k un ko recharge krtay jayein gy
        # jahan kahi bhi double jump ki zarort ho ghi hum 2 ko request kr lyn gy
        
        if N <= 2:
            outt_val.append("YES"); continue
        idx = np.arange(1, N + 1, dtype=np.int64) * R
        C = np.maximum.accumulate(a - idx) + idx + R
        outt_val.append("YES" if bool((C[:-2] <= a[2:]).all()) else "NO")
    sys.stdout.write("\n".join(outt_val) + "\n")


main()
