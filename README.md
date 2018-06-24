# cThredgeCorr

For fast generation of edge lists from the thresholded correlated edge weight model. 
It's recommended to install https://github.com/benmaier/ThredgeCorr in concurrence to improve
usability.

## Install

For all systems, first clone this repository.

Install

    $ pip install ./cThredgeCorr

Install development version (stored in this directory)

    $ pip install -e ./cThredgeCorr --no-binary :all:

## Examples

```python
from ThredgeCorr import FastThredgeCorrGraph
from cThredgeCorr import get_edge_list

F = FastThredgeCorrGraph(N=100,covariance=0.3,mean_degree=3)
edge_list = get_edge_list(F.N, F.b, F.t, F.parameters)
```
