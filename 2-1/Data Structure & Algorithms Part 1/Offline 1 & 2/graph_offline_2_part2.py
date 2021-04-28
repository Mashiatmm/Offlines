import numpy as np
from matplotlib import pyplot as plt

x=np.arange(1,31,1)
y=np.array([1048,2456,3213,4168,7314,17258,34620,52398,140551,3953480,
            1001000,1992000,4988000,7979000,16952000,17951000,24969000,85768000,136635000,277258000,
            581441000,578452000,1193810000,4761260000,6868970000,13294400000,38966700000,78653600000,109198000000,121642000000])


plt.figure(figsize=(10,8))
plt.plot(x,y)
plt.grid(color='grey',linewidth=0.5)
plt.title('Time of computing distinct subsets of a set of given size')
plt.xlabel('Set Size')
plt.ylabel('Running Time')
plt.savefig('subset.pdf')
