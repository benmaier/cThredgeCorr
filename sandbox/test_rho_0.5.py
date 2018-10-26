    
import numpy as np

from scipy.optimize import newton
from scipy.special import erf
from ThredgeCorr import get_degrees_from_edge_list
from cThredgeCorr import get_fast_edge_list

#import matplotlib.pyplot as pl
from bfmplot import pl

from time import time


def pk(k, n, t, rho):

    a0 = 2.30753
    a1 = 0.27061
    b1 = 0.9929
    b2 = 0.04481

    x = 1-k/(n-1)
    low_x = x[x<=0.5]
    high_x = 1-x[x>0.5]
    ck = []

    for ix, x_ in enumerate([low_x,high_x]):
        s = np.sqrt(np.log(1/x_**2))
        this_phi = (a0+a1*s) / (1+b1*s + b2*s**2) - s
        prefac = 1 - 2*ix
        ck.append(prefac*this_phi)

    ck = np.concatenate(ck)
    print(ck.shape)

    print((2*rho-1)/(2*rho) * ck**2)

    fac = 1/(n-1)*np.sqrt((1-rho)/rho) * np.exp(-t**2/2/rho)
    return fac * np.exp((2*rho-1)/(2*rho) * ck**2 + t*np.sqrt(1-rho)/rho * ck)


N_meas = 10

def ccdf(x):
    return 1 - 0.5*(1 + erf(x/np.sqrt(2)))

def get_threshold(N, mean_degree):
    p = mean_degree / (N-1.0)
    t = newton(lambda x: ccdf(x) - p, 0)
    return t

N = 10000
covariance = 0.5
mean_degree = 20 

t = get_threshold(N, mean_degree)

k1 = []

#np_edges = T.get_n_edge_lists(500)

for meas in range(N_meas):
    edges = get_fast_edge_list(N, covariance, t)
    ks = get_degrees_from_edge_list(N,edges).tolist()
    k1.extend(ks)

k1 = np.array(k1,dtype=int)
k1pos = k1[k1>=1]

import powerlaw
results = powerlaw.Fit(k1pos,discrete=True,xmin=1)

fig = pl.figure()
powerlaw.plot_ccdf(k1pos)
#powerlaw.plot_pdf(k1)
#pl.hist(k1,bins=np.arange(1,max(k1)+1),histtype='step',density=True)
x = np.arange(1,max(k1pos))
results.lognormal.plot_ccdf(ax=pl.gca())
#results.lognormal.plot_pdf(ax=pl.gca())

pl.xscale('log')
pl.yscale('log')

fig = pl.figure()
pl.hist(k1,bins=np.arange(max(k1)+1),histtype='step',density=True,
            label=r'10 networks, $N=10^4,\rho=0.5,\left\langle k\right\rangle = 2$')
x = np.arange(1,max(k1pos))

a0 = 2.30753
a1 = 0.27061
b1 = 0.9929
fac = (a1 - a0*b1 - 1)
s = np.sqrt(2*x/(N-1))
s = np.sqrt(np.log(1/(1-x/(N-1))**2))
#pl.plot(x, 1/(N-1)*np.sqrt((1-covariance)/covariance) * np.exp(-t**2/2/covariance+np.sqrt(2)*t*a0)* np.exp(np.sqrt(2)*fac*t*np.sqrt(2*x/(N-1))))
#pl.plot(x, 1/(N-1)*np.sqrt((1-covariance)/covariance) * np.exp(-t**2/2/covariance+np.sqrt(2)*t*a0)* np.exp(-np.sqrt(2)*fac*t*s))
#pl.plot(x, 1/(N-1)*np.sqrt((1-covariance)/covariance) * np.exp(-t**2/2/covariance)*\
#           np.exp(-fac*np.sqrt(2*np.log((N-1)/x)))
#           )
rho = covariance
prefac = 1/(N-1)*np.sqrt((1-rho)/rho) * np.exp(-t**2/2/rho)
pl.plot(x, pk(x, N, t, covariance), label='asymptotic solution Eq. (29)')
pl.plot(x, 1/x**(np.sqrt(2))*0.1,label='$1/k^{\sqrt{2}}$')
#pl.plot(x, prefac*np.exp(np.sqrt(2)*t*1/(x/(N-1))**0.5/3.25),label='stretched exponential')
pl.plot(x, prefac*np.exp(np.sqrt(2)*t*np.sqrt(2*np.log((N-1)/x)))/15,label='mu log')

pl.legend()

pl.xscale('log')
pl.yscale('log')

pl.xlabel('degree $k$')
pl.ylabel('probability')
fig.tight_layout()

fig.savefig('degree_asymptotic.png',dpi=200)

pl.show()

#print(np.array(k).mean())
#print("Transitivity from networks =", np.array(C1).mean())
#print("Transitivity from 3-cliques =", A.estimate_transitivity(int(binom(N,3))*50))
