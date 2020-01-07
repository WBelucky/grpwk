
from matplotlib import pyplot as plt
import numpy as np


plt.xlabel("length of s")
plt.ylabel("number")
for i in range(5):
    print("data{}".format(i))
    with open("../data/dat{}_ref".format(i)) as f: 
        arr = []
        sigma = 0
        strs = f.readline()
        for i, c in enumerate(strs):
            if c == 'b':
                sigma += 1
            if i % 100 == 0:
                arr.append(sigma)
                sigma = 0;
        while arr[-1] == 0:
            arr.pop()
        print("\tmax length        :{}".format(len(arr)))
        y = np.array(arr)
        plt.plot(y)
plt.show()

