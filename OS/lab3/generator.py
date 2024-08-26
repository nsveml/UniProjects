#!/usr/bin/python3
import sys
import numpy as np
if (len(sys.argv) == 1):
    size = int(input())
else:
    size = int(sys.argv[1])
arr = np.random.uniform(low = 0, high = 100000, size = size).astype(int)
for i in arr: print(i, end = ' ')
print("\n")
#arr.sort()
#for i in arr: print(i, end = ' ')
#print("\n")

