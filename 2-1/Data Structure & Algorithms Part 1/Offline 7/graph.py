from matplotlib import pyplot as plt

x=[10,100,500,1000,2000,5000]
merge_avg=[0.01	,14.385,229,450	,804,3296]
merge_best=[0.05,12.398,197	,339,746,5196]
merge_worst=[0.007,13.085,150,345,850,4234]

quick_avg=[0.018,	10.209,	278	,503	,1023	,2548]
quick_best=[0.02,	110.695,	2755	,11885	,48910	,293055]
quick_worst=[0.008,	61.812,	2529	,9289	,35266,	223734]

plt.figure(figsize=(10,8))
plt.plot(x,merge_avg,label='Merge Random Case',color='red')
plt.plot(x,quick_avg,label='Quick Random Case',color='blue')
plt.grid(color='grey',linewidth=0.5)
plt.title('Comparison of Random Case')
plt.xlabel('size of array')
plt.ylabel('time in microseconds')
plt.legend(loc='upper left')
plt.savefig('random.pdf')
plt.show()

plt.figure(figsize=(10,8))
plt.plot(x,merge_best,label='Merge Ascending Case',color='red')
plt.plot(x,quick_best,label='Quick Ascending Case',color='blue')
plt.grid(color='grey',linewidth=0.5)
plt.title('Comparison of Ascending Case')
plt.xlabel('size of array')
plt.ylabel('time in microseconds')
plt.legend(loc='upper left')
plt.savefig('ascending.pdf')
plt.show()

plt.figure(figsize=(10,8))
plt.plot(x,merge_worst,label='Merge Descending Case',color='red')
plt.plot(x,quick_worst,label='Quick Descending Case',color='blue')
plt.grid(color='grey',linewidth=0.5)
plt.title('Comparison of Descending Case')
plt.xlabel('size of array')
plt.ylabel('time in microseconds')
plt.savefig('descending.pdf')
plt.legend(loc='upper left')
plt.show()

plt.figure(figsize=(10,8))
plt.plot(x,merge_worst,label='Merge Descending Case',color='red')
plt.plot(x,merge_avg,label='Merge Avg Case',color='blue')
plt.plot(x,merge_best,label='Merge Ascending Case',color='green')
plt.grid(color='grey',linewidth=0.5)
plt.title('Comparison of Merge Sort Cases')
plt.xlabel('size of array')
plt.ylabel('time in microseconds')
plt.legend(loc='upper left')
plt.savefig('merge.pdf')

plt.show()


plt.figure(figsize=(10,8))
plt.plot(x,quick_worst,label='Quick Descending Case',color='red')
plt.plot(x,quick_avg,label='Quick Avg Case',color='blue')
plt.plot(x,quick_best,label='Quick Ascending Case',color='green')
plt.grid(color='grey',linewidth=0.5)
plt.title('Comparison of Quick Sort Cases')
plt.xlabel('size of array')
plt.ylabel('time in microseconds')
plt.legend(loc='upper left')
plt.savefig('quick.pdf')

plt.show()