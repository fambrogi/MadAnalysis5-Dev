import os,sys
import os,sys
import matplotlib

matplotlib.use('Agg')

from matplotlib import ticker
import matplotlib.pyplot as plt

import numpy as np
from matplotlib.ticker import MultipleLocator, FormatStrFormatter


F_1400 = 'T1_1400_histo.dat'
F_1800 = 'T1_1800_histo.dat'

F_1800_2 = 'T1_1800_1000_histo2.dat'

# order in file:     cout << Meff << "_" << MET_HT << "_" << MET << "_" << HT << endl; 

def plot(F):
    tit = F.replace('_histo.dat','_1000')
    plt.title('Distributions for ' + tit  )
    meff , ht , met, metht = [], [], [], []
    a = open(F, 'r').readlines()[50:-50]
    a = [ a for a in a if a and '>' not in a ]
    for b in a:
       try:
   	 b = b.split('_')
   	 meff.append(float(b[0]))
       	 ht.append(float(b[3]))
   	 met.append(float(b[2]))
   	 metht.append(float(b[1]))
       except: 
	pass
    plt.yscale('log')
    plt.hist(meff , bins = 200, histtype = 'step', label = 'Meff', color = 'blue')
    plt.hist(ht , bins = 200, histtype = 'step', label = 'HT', color = 'red')
    plt.hist(met , bins = 200, histtype = 'step', label = 'MET', color = 'lime')

    plt.legend()
    plt.savefig(tit +'_meff.png')
    plt.close()
   
    print(metht)
    plt.yscale('log')
    metht = [ a for a in metht if a < 1000 ]
    plt.hist(metht ,bins = 200, histtype = 'step', color = 'gold', label = 'MET/sqrt(HT)')
    plt.legend()
    plt.savefig(tit + '_metht.png')
    plt.close()

plot(F_1400)
plot(F_1800)


plot(F_1800_2)


