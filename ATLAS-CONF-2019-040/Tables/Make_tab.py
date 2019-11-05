import os,sys


def replacer(stringa= ''):

    stringa = stringa.replace('Prese', '$Preselection$')
    stringa = stringa.replace('Jet>', '$n_j>$')
    stringa = stringa.replace('Jet >', '$n_j>$')
    stringa = stringa.replace('Dphi(j3)>', '$\Delta \phi(j_{1,2,(3)},p_T^{miss})>$')
    stringa = stringa.replace('Dphi(rest)>', '$\Delta \phi(j_{i>3},p_T^{miss})>$') 
    stringa = stringa.replace('pt(j1)>', '$p_T(j_2)>$')
    stringa = stringa.replace('pt(j2)>', '$p_T(j_2)>$')
    stringa = stringa.replace('pt(j4)>', '$p_T(j_4)>$')
    stringa = stringa.replace('pt(j6)>', '$p_T(j_6)>$')
    stringa = stringa.replace('eta(j1j2)<','$|\eta(j_{1,2}|<$')
    stringa = stringa.replace('eta(j4)<','$|\eta(j_{1,2,3,4}|<$')
    stringa = stringa.replace('eta(j4)<','$|\eta(j_{1,2,3,4,5,6}|<$')
    stringa = stringa.replace('Etmiss_HT>','$E_T^{miss}/\sqrt{H_T}>16 GeV^{1/2}$')
    stringa = stringa.replace('Meff>','$m_{eff}>$')
    stringa = stringa.replace('Meff','$m_{eff}>$')
    stringa = stringa.replace('Etmiss/HT','$E_T^{miss}/\sqrt{H_T}$')
    stringa = stringa.replace('Aplanarity>','Aplanarity$>$')
    stringa = stringa.replace('eta(j6)<','$|\eta(j_{1,2,3,4,5,6}|<$')


    return stringa
def make_table(F = 'T1.csv'):
    a = open(F, 'r').readlines()
    for l in a:
        s = l.split(',')
        line = ''
        for v in s:
	    c = replacer(stringa = v)
            if s.index(v)==12:  # 4 or 15
                 line = line + c + '\\\\' 
            else:
                 line = line + c + '&' 
             
        print line

make_table(F = 'T5_SR5.csv')



