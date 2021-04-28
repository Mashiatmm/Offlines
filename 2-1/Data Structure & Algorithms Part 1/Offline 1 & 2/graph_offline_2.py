from matplotlib import pyplot as plt
import numpy as np

x=np.array([10,100,200,500,1000,2000,5000,10000])

Selection_Avg=np.array([596.1,20579.8,60931.4,460927,1759400,7086290,44507000,176175000])
Insertion_Avg=np.array([402.9,15228.5,50052.3,271174,1122850,4357230,28454800,112191000])

Selection_Best=np.array([299.9,16404.3,70404.1,459308,1706580,6991590,44066800,175391000])
Insertion_Best=np.array([198.1,398.9,598.9,1562.5,2160.8,11404.6,23913,55914])

Selection_Worst=np.array([699.2,22722.6,82794.8,531847,1835860,7393240,48356800,199250000])
Insertion_Worst=np.array([499.5,19819.8,93827.5,555128,2197880,8813890,56829900,222601000])

plt.figure(figsize=(10,8))

plt.plot(x,Selection_Avg,label='Selection Avg Case')
plt.plot(x,Insertion_Avg,label='Insertion Avg Case',color='red')
plt.scatter(x,Insertion_Avg,color='red')
plt.scatter(x,Selection_Avg)
plt.grid(color='grey',linewidth=0.5)
plt.title('Comparison between Selection and Insertion Sort')
plt.xlabel('value of n')
plt.ylabel('Running time in Microseconds')
plt.legend(loc='upper left')
plt.savefig('avg_case.pdf')
plt.show()

plt.figure(figsize=(10,8))
plt.plot(x,Selection_Best,label='Selection Best Case',color='blue')
plt.plot(x,Insertion_Best,label='Insertion Best Case',color='red')
plt.scatter(x,Insertion_Best,color='red')
plt.scatter(x,Selection_Best,color='blue')
plt.grid(color='grey',linewidth=0.5)
plt.title('Comparison between Selection and Insertion Sort')
plt.xlabel('value of n')
plt.ylabel('Running time in Microseconds')
plt.legend(loc='upper left')
plt.savefig('best_case.pdf')
plt.show()

plt.figure(figsize=(10,8))
plt.plot(x,Selection_Worst,label='Selection Worst Case',color='blue')
plt.plot(x,Insertion_Worst,label='Insertion Worst Case',color='red')
plt.scatter(x,Insertion_Worst,color='red')
plt.scatter(x,Selection_Worst,color='blue')
plt.grid(color='grey',linewidth=0.5)
plt.title('Comparison between Selection and Insertion Sort')
plt.xlabel('value of n')
plt.ylabel('Running time in Microseconds')
plt.legend(loc='upper left')
plt.savefig('worstcase.pdf')
plt.show()