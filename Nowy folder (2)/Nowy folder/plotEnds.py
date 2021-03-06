import sys
import numpy as np
import matplotlib.pyplot as plt
from numpy.lib import median

def gauss(data, passLines=False):
    mean = sum([ k*v for k, v in data.items()])/sum(data.values())
    mse = sum([v*(k - mean)**2 for k, v in data.items()])/sum(data.values())
    rmse = np.sqrt(mse)
    mx = max([ v for k, v in data.items()])
    med = np.median([ k*v for k, v in data.items()])
    xMedian = np.median(tuple(data.keys()))


    #ret = [ (mx * np.exp( -((x - xMedian)**2) / (2*mse) )) / (rmse*np.sqrt(2*np.pi)) for x in data.keys()]
    ret = [ (mx * np.exp( -(((x - xMedian))**2)/(2*mse)  )) for x in data.keys()]
    if not passLines:
        print("the chid is around",3*rmse)
        plt.plot([3*rmse,3*rmse], [0,sum(data.values())/10], "g-o")
        plt.plot([-3*rmse,-3*rmse], [0,sum(data.values())/10], "g-o", label="3 sigma")
    return ret

def gaussCircle2D(dataX, dataY):
    meanX = sum([ k*v for k, v in dataX.items()])/sum(dataX.values())
    mseX = sum([v*(k - meanX)**2 for k, v in dataX.items()])/sum(dataX.values())
    rmseX = np.sqrt(mseX)

    meanY = sum([ k*v for k, v in dataY.items()])/sum(dataY.values())
    mseY = sum([v*(k - meanY)**2 for k, v in dataY.items()])/sum(dataY.values())
    rmseY = np.sqrt(mseY)

    plt.plot(dataX.keys(), gauss(dataX, passLines=True), "aqua", label="normal dist. X")
    plt.plot(gauss(dataY, passLines=True), dataY.keys(), "cyan", label="normal dist. Y")

    print("the chid is around |X|",3*rmseX)
    print("the chid is around |Y|",3*rmseY)
    theta = np.linspace(-np.pi, np.pi, 200)
    plt.plot(np.sin(theta)*3*rmseX, np.cos(theta)*3*rmseY, "g-", label="3 sigma")
    #plt.plot([3*rmse,3*rmse], [0,sum(dataX.values())/10], "g-o")
    #plt.plot([-3*rmse,-3*rmse], [0,sum(dataX.values())/10], "g-o")


if(sys.argv[1] == "1"):
    x = np.loadtxt('walks/endOfWalks_1D.txt', unpack=True)
    plt.scatter(x, range(0,len(x)), marker="x")
    
    valCount = dict()
    for pos in x:
        if pos in valCount:
            valCount[pos] += 10
        else:
            valCount[pos] = 0
    valCount = {k: v for k, v in sorted(valCount.items(), key=lambda item: item[0])}
    plt.plot(valCount.keys(), gauss(valCount), "cyan", label="normal dist.")
    plt.plot(valCount.keys(), valCount.values(), "r-", label="dist.")
    plt.title("1D random walk ends")
    plt.xlabel("X")
    plt.ylabel("child")
    """
        #1D
        bradziej prawdopodobne jest to ??e dziecko b??dzie blisko miejsca gdzie si?? zgubi??o
        patrz??c na przyk??ady z 1 krokiem i 30
        to wi??ksze prawdopodobie??stwo jest ??e b??dzie w odleg??o??ci 1 ni?? 30 
        jednak wykres rozk??adu w 30 krokach jeszcze nie jest na samym dole i 
        prawdopodobie??stwo ??e tam znajdzie si?? dziecko jest dalej wyskokie  
  
        odleg??o??ci?? za jak?? mo??na uzna?? ??e dziecko nie przekroczy
        jest "3*sigma" gdzie sigma to odchylenie standardowe 
        ko??cowych pozycji dzieci. 3*sigma daje nam prawdopodobie??stwo r??wne 99.7%
        ??e dziecko znajdzie si?? w tej odleg??o??ci. oczywi??cie ta odleg??o????
        nie zapewnia nam ??e dziecko nie mo??e by?? ju?? dalej, ale daje nam du???? przewag?? 
        w znale??ienu dziecka ni?? mieli by??my przeszukiwa?? caly zakres 1000 krok??w. 
        Co te?? jest jednak mo??liwe ??eby dziecko sz??o ca??y czas prosto.
        jednak fakt ??e jest zagubione i nie wie gdzie is?? sprawia ??e 
        w pewien sos??b kr????y wok???? miejsca startu.
        Im d??u??ej chodzi jednak tym dalej mo??e si?? oddali??    

        Warto???? graniczna to 94.8 krok??w
    """


if(sys.argv[1] == "2"):
    x, y = np.loadtxt('walks/endOfWalks_2D.txt', unpack=True)
    plt.scatter(x, y, marker="x")

    valCountX = dict()
    valCountY = dict()
    populationScale = max(x)/(len(x)/50)
    for pos in x:
        if pos in valCountX:
            valCountX[pos] += populationScale
        else:
            valCountX[pos] = 0

    for pos in y:
        if pos in valCountY:
            valCountY[pos] += populationScale
        else:
            valCountY[pos] = 0

    valCountX = {k: v for k, v in sorted(valCountX.items(), key=lambda item: item[0])}
    valCountY = {k: v for k, v in sorted(valCountY.items(), key=lambda item: item[0])}
    gaussCircle2D(valCountX, valCountY)
    plt.plot(valCountX.keys(), valCountX.values(), "crimson", label="dist. X")
    plt.plot(valCountY.values(), valCountY.keys(), "deeppink", label="dist. Y")
    plt.axis('equal')
    plt.title("2D random walk ends")
    plt.xlabel("X")
    plt.ylabel("Y")
    """
        #2D
        jak w przypadku 1D, prawdopodobnie dziecko te?? nie oddali si??
        dalej ni?? na pewn?? odleg??o????. Wiad?? wyra??ny promie??,
        w kt??rym dziecko mo??e si?? znale????.

        w tej anali??ie zbada??em osobno przemieszczenie x i y
        nast??pnie wyniki obu wykorzysta??em do narysowania elipesy
        w kt??rej polu dziecko mo??e si?? znale????

        warto??c graniczna dla X i Y wynosi 65.4 z ma???? r????nic??
        po liczbach dziei??tnych. Mimo ??e statystycznie dziecko
        wykonuje po??ow?? ruch??w w tyko jednym kieruku to warto????
        graniczna nie jest o po??owe mniejsza a wynosi oko??o 2/3 

        por??wna??em t?? warto???? dla 1D 500 krok??w, tam odchyleniem granicznym by??o 66.7
        zale??no???? ta wydaje mi si?? by?? zwi??zana z zadaniem 6 na tej li??cie

    """


plt.legend()    
plt.show()