import sys
import numpy as np
import matplotlib.pyplot as plt

# usage - <program name> <file name>

"""
"""


s, i = np.loadtxt(sys.argv[1], unpack=True)

plt.scatter(s, s, "b", label="a")
plt.scatter(i, i, "r", label="b")
#plt.plot(range(len(s)), q, "c-", label="ek2")
#plt.plot(range(len(s)), w, "y-", label="ep2")
#plt.plot(range(len(s)), e, "m-", label="ec2")




#plt.xscale("log")
#plt.yscale("log")



plt.legend()    
plt.show()