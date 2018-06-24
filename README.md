# cThredgeCorr

For fast simulations of diffusion processes on networks.

## Install

For all systems, first clone this repository.

### Python

Install

    $ pip install ./cNetworkDiff

Install development version (stored in this directory)

    $ pip install -e ./cNetworkDiff --no-binary :all:


### Matlab (Mac OSX)

You need to have the current XCode version installed (free in AppStore). Open Matlab and change into the directory of the repository. At first, there's two files you need to change.

```matlab
>>> cd /path/to/repository
>>> edit ([matlabroot '/bin/maci64/mexopts/clang++_maci64.xml'])
>>> edit ([matlabroot '/bin/maci64/mexopts/clang_maci64.xml'])
```

In both files, copy lines matching occurences of `MacOSX10.x.sdk` and change `MacOSX10.x.sdk` to `MacOSX10.11.sdk`(or whichever current version of XCode you're using).

Now, run


```matlab
>>> setup
>>> cd sandbox
>>> matlab_test
```

## Examples

### Python

There's some examples in the folder sandbox, e.g. `sandbox/nwdiff_test.py`. 

Here's an example to get a single saturation time.


```python

from cNetworkDiffusion import saturation_time

N = 2
E = [(0,1)]

source = 0
target = 1

N_walker = 10
N_saturation = 5

t = saturation_time(N,E,source,target,N_walker,N_saturation)
```

And example on how to get a distribution of saturation times

```python
from cNetworkDiffusion import saturation_time

print("Let's do a histogram on this graph")
print("     o")
print("    /|\\")
print("   S | T")
print("    \\|/")
print("     o")
print("where S is the source node and T is the target node")
print("simulating ...")

saturation_times = []
N_meas = 1000
N_walker = 1000
N_saturation = 950

E = [ (0, 1), (0, 2), (1,2), (1, 3), (2, 3) ]
N = max([ node for e in E for node in e ]) + 1

source = 0
target = 3

from collections import Counter

for meas in range(N_meas):
    t = saturation_time(N,E,source,target,N_walker,N_saturation,seed=meas)    
    saturation_times.append(t)

max_t = max(saturation_times)

# get histogram
hist = Counter(saturation_times)

length = 30
max_str_len = str(len(str(max_t)))
fmt_str = '{:0'+max_str_len+'d}'

print("saturation times")
print("================")
print((" " * (int(max_str_len)-1)) + "t: probability")
print("-"*length)
for t in range(1,max_t+1):
    this_length = round(hist[t] / float(N_meas) * length)
    print( (fmt_str + ': ' + '#' * this_length).format(t))
```
