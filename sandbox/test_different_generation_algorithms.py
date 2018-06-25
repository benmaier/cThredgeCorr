    
import numpy as np
from scipy.special import binom
from ThredgeCorr import FastThredgeCorrGraph
from ThredgeCorr import ThredgeCorrGraph
from ThredgeCorr import get_degrees_from_edge_list
from cThredgeCorr import get_edge_list, get_fast_edge_list
import networkx as nx
import matplotlib.pyplot as pl



from time import time
N = 150

N_meas = 10


start = time()
A = ThredgeCorrGraph(N,0.49,.5)
[ A.get_new_edge_list() for n in range(N_meas) ]
end = time()

print("std method; N =", N, '; generating ', N_meas, 'networks took', end-start, 'seconds')

start = time()
numpymethod = FastThredgeCorrGraph(N,0.49,.5)
[ numpymethod.get_new_edge_list() for n in range(N_meas) ]
end = time()

print("py fast method; N =", N, '; generating ', N_meas, 'networks took', end-start, 'seconds')

start = time()
numpymethod = FastThredgeCorrGraph(N,0.49,.5)
[ get_edge_list(N,0.49,numpymethod.t,numpymethod.parameters) for n in range(N_meas*100) ]
end = time()

print("cpp fast method; N =", N, '; generating ', N_meas*100, 'networks took', end-start, 'seconds')

start = time()
numpymethod = FastThredgeCorrGraph(N,0.49,.5)
[ get_fast_edge_list(N,0.49,numpymethod.t,numpymethod.parameters) for n in range(N_meas*100) ]
end = time()

print("cpp fast fast method; N =", N, '; generating ', N_meas*100, 'networks took', end-start, 'seconds')
k1 = []
k2 = []
k3 = []
k4 = []

#np_edges = T.get_n_edge_lists(500)

for meas in range(1000):
    edges = A.get_new_edge_list()
    ks = get_degrees_from_edge_list(N,edges).tolist()
    k1.extend(ks)

    edges = numpymethod.get_new_edge_list()
    ks = get_degrees_from_edge_list(N,edges).tolist()
    k2.extend(ks)

    edges = get_edge_list(N,numpymethod.b,numpymethod.t,numpymethod.parameters)
    ks = get_degrees_from_edge_list(N,edges).tolist()
    k3.extend(ks)

    edges = get_fast_edge_list(N,numpymethod.b,numpymethod.t,numpymethod.parameters)
    ks = get_degrees_from_edge_list(N,edges).tolist()
    k4.extend(ks)

pl.hist(k1,bins=np.arange(max(k1)+1),histtype='step')
pl.hist(k2,bins=np.arange(max(k1)+1),histtype='step')
pl.hist(k3,bins=np.arange(max(k1)+1),histtype='step')
pl.hist(k4,bins=np.arange(max(k1)+1),histtype='step')
pl.xscale('log')
pl.yscale('log')

pl.show()

#print(np.array(k).mean())
#print("Transitivity from networks =", np.array(C1).mean())
#print("Transitivity from 3-cliques =", A.estimate_transitivity(int(binom(N,3))*50))
