import numpy as np

def read_input():
    N = input()
    N = int(N)
    line = input().split()
    Y = [int(_) for _ in line]
    data = []
    
    for _ in range(N):
        line = input().split()
        sz = line.size()
        for x in line:
            data.append(int(x))

    mat = np.matrix(data, (N, sz))
