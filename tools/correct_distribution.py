
from matplotlib import pyplot as plt
import numpy as np


plt.xlabel("length of s")
plt.ylabel("number")
with open("../log.txt") as f: 
    arr = []
    sigma = 0
    in_str = f.readline()
    out_str = f.readline()
    ans_str = f.readline()
    
    span = 10000
    for i in range(len(in_str)):
        if out_str[i] == ans_str[i]:
            sigma +=1
        if i % span == 0:
            arr.append(sigma / span)
            sigma = 0
    while arr[-1] == 0:
        arr.pop()
    y = np.array(arr)
    plt.plot(y)
plt.show()

