import sys
import numpy as np
from numpy.lib import median
import matplotlib.pyplot as plt


def gauss(data):
    mean = sum([ k*v for k, v in data.items()])/sum(data.values())#średnia
    mse = sum([v*(k - mean)**2 for k, v in data.items()])/sum(data.values())#wariacia
    rmse = np.sqrt(mse)#odchylenie
    mx = max([ v for k, v in data.items()])
    med = np.median([ k*v for k, v in data.items()])

    ret = [ (mx * np.exp( -(((x - med))**2)/(2*mse)  )) for x in data.keys()]#rozklad normalny
    print("dzieci najprawdopodbniej są w odlgełośći ",3*rmse, "kroków")
    return ret

def main():
    x = np.loadtxt('spacery/odlegloscPo1000.txt', unpack=True)
    valCount = dict()
    for pos in x:
        if pos in valCount:
            valCount[pos] += 10
        else:
            valCount[pos] = 0
    valCount = {k: v for k, v in sorted(valCount.items(), key=lambda item: item[0])}
    plt.plot(valCount.keys(), gauss(valCount))
    plt.xlabel("X")
    plt.ylabel("dzieci")

if __name__ == "__main__":
    main()
	
plt.legend()    
plt.show()


	# Bardziej prawdopodobne jest to, że dziecko będzię bliżej odległości 1
	# Odległośc 3sigma można uznać, za wartość graniczną gdzię znajduję się 
	# 99.7% procent wszystkich dzieci
