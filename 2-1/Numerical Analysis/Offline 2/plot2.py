import numpy as np
import matplotlib.pyplot as plt

input=open("in2.txt","r")

if(input.mode=="r"):
    line=[]
    s=input.readline()
    while(s!=''):
        line.append(s)
        s=input.readline()
input.close()

print(line) 

x=np.linspace(0,100,2000)

y=[]
max_value=0
for i in range(1,len(line)):
    eqn=line[i].split(' ')
    y.append((float(eqn[2])-float(eqn[0])*x)/float(eqn[1]))
    for i in eqn:
        if(max_value<float(i)):
            max_value=float(i)
   
for i in y:
    plt.plot(x,i)    
    
plt.xlim(0,20)
plt.ylim(0,20)

constraints=np.asarray(y).min(0)
restrict=[0]*2000
print(constraints)
plt.fill_between(x, constraints,restrict,where=constraints>restrict, color='grey', alpha=0.5)
plt.show()