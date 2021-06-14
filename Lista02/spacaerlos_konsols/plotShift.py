import sys
import numpy as np
import matplotlib.pyplot as plt

"""
    dzieći są nie przewidywalne
    można się ich bać
"""


x, x2, srx2 = np.loadtxt('walks/shift_%sD_diagonal.txt'%(2), unpack=True)
y, y2, sry2 = np.loadtxt('walks/shift_%sD.txt'%(2), unpack=True)
srz2 = np.loadtxt('walks/odlegloscPo1000.txt', unpack=True)
#plt.title("2D random walk")
plt.xlabel("czas")
plt.ylabel("średnia odległośź")
#plt.plot(range(len(x)), x)
#plt.plot(range(len(x)), x2)
#plt.plot(range(len(y)), y)
#plt.plot(range(len(y)), y2)
#plt.legend()    
#plt.show()

xxx = range(0,10000,1)
yyy = [x*10 for x in xxx]


plt.plot(range(len(x)), srx2,"r",label="8kierunków_las")
plt.plot(range(len(y)), sry2,"b",label="4kierunki_las")
#plt.plot(xxx, yyy,"g",label="pole")

plt.legend()    
plt.show()