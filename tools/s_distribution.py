from matplotlib import pyplot as plt
import numpy as np


plt.xlabel("length of s")
plt.ylabel("number")
for i in range(5):
    print("data{}".format(i))
    with open("../data/dat{}_in".format(i)) as f: 
        _ = f.readline()
        arr = [0] * 1000000
        strs = f.readlines()
        print("\ttotal number of s: {}".format(len(strs)))
        for s in strs:
            arr[len(s)] += 1
        while arr[-1] == 0:
            arr.pop()
        print("\tmax length        :{}".format(len(arr)))
        y = np.array(arr)
        plt.plot(y)
plt.show()

