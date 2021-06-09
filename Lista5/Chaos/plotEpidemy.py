import sys
import numpy as np
import matplotlib.pyplot as plt

# usage - <program name> <file name>

"""
"""


s, i, r, q,w,e = np.loadtxt(sys.argv[1], unpack=True)

plt.plot(range(len(s)), s, "b-", label="ek")
plt.plot(range(len(s)), i, "r-", label="ep")
plt.plot(range(len(s)), r, "g-", label="ec")
#plt.plot(t, t**(1.75), "b-", label="N**(1.74)")

plt.xlabel("czas")
plt.ylabel("energia")



#plt.xscale("log")
#plt.yscale("log")



plt.legend()    
plt.show()