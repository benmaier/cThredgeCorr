from cThredgeCorr import get_edge_list
from ThredgeCorr import FastThredgeCorrGraph


G = FastThredgeCorrGraph(25000, 0.49, mean_degree = 20)

E = get_edge_list_memory_friendly(G.N, G.b, G.t, G.parameters)

print("number of edges =", len(E))

from time import sleep

sleep(5)
