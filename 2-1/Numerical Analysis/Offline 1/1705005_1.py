from matplotlib import pyplot as plt
import numpy as np
import matplotlib as mp

def findLn(x,n):
    i=1;
    result=0
    term=1
    sign=-1.0
    while i<=n:
        sign*=-1.0
        term*=x
        result+=term*sign/i
        i+=1  
    return result

x=float(input("Value of x: "))
n=int(input("Number of iterations: "))

result=findLn(x,n)

print('ln(1+x) when x=',x,'and i=',n,'is= ',result)

temp_array=np.array([n,1,3,5,20,50])

x_axis=np.arange(1,-1,-0.1)
y_axis=np.log(1+x_axis)
y_axises=[list(map(findLn,x_axis,[n]*20))]
for i in range(1,6):
    y_axises.append(list(map(findLn,x_axis,[temp_array[i]]*20)))

colors=np.array(['red','yellow','purple','green','orange','cyan'])

plt.figure(figsize=(10,8))
for i in range(0,6):
    plt.plot(x_axis,y_axises[i],color=colors[i],linewidth=2,label='ln(1+x) for {}'.format(temp_array[i]))


plt.plot(x_axis,y_axis,color='black',linewidth=2,label='ln(1+x)',dashes=[10,2,2,2,2,2])

plt.grid(color='grey',linewidth=0.5)
plt.title('ln(1+x) VS x Graph')
plt.legend(loc='upper left')
plt.xlabel('value of x')
plt.ylabel('value of ln(1+x)')
plt.xlim(-1,1.1,0.1)

plt.show()

value=[]

j=1;
result=0
term=1
sign=-1.0

for i in range(1,51):
    sign*=-1.0
    term*=0.5
    result+=term*sign/i
    value.append(result)
    
def findError(value,i):
    if i==1:
        ApproxError=100
    else:
        ApproxError=(abs(value[i-1]-value[i-2])/value[i-1])*100
        
    return ApproxError
    

x_axis=np.arange(1,51,1)
y_axis=list(map(findError,[value]*50,x_axis))
    
plt.figure(figsize=(10,8))
plt.plot(x_axis,y_axis,linewidth=2,label='Relative Approx. Error')

plt.grid(color='grey',linewidth=0.5)
plt.title('Relative Approx. Error Graph VS iteration number for ln(1.5)')
plt.legend(loc='upper left')
plt.xlabel('Number of Terms')
plt.ylabel('Relative Approx. Error')
plt.show()
