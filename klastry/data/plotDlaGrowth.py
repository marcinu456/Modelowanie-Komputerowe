import sys
import numpy as np
import matplotlib.pyplot as plt

"""
"""


t, r = np.loadtxt(sys.argv[1], unpack=True)

plt.plot(t, r, "ro", label="r")
plt.plot(t, [rr*2 for rr in r], "mo", label="d")
#plt.plot(t, t**(1.75), "b-", label="N**(1.74)")
plt.title("cluster radius over time DLA 0")
plt.xlabel("time")
plt.ylabel("R")

print(sum([float(np.log(t[i], r[i])) for i in range(len(t))])/len(t))

plt.xscale("log")
plt.yscale("log")



plt.legend()    
plt.show()