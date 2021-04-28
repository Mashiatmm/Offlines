from matplotlib import pyplot as plt
import numpy as np

def PowerArraySum(PowerArray,X,m,Summation_Of_Power):
    length=len(Summation_Of_Power)
    #m needs to be 2*m for m*m matrix and m for m*1 matrix
    for i in range(length-1,m):
        PowerArray=np.multiply(PowerArray,X)
        Summation_Of_Power.append(np.sum(PowerArray))
    return PowerArray
        
def Form_X_Matrix(Summation_Of_Power,n):
    X_Matrix=np.zeros((n+1,n+1))
    for i in range(n+1):
        for j in range(n+1):
            X_Matrix[i][j]=Summation_Of_Power[i+j]
    return X_Matrix

f=open("data.txt","r")

if(f.mode=='r'):
    X=[]
    Y=[]
    input=f.readline()
    while(input!=''):
        var=input.split(' ')
        X.append(float(var[0]))
        Y.append(float(var[1]))
        input=f.readline()
f.close()

n=3

length_of_data=len(X)
PowerArray=[1]*length_of_data
Summation_Of_Power=[]
Summation_Of_Power.append(np.sum(PowerArray))


RHS_Matrix=[]
RHS=Y
RHS_Matrix.append(np.sum(RHS))

avg_y=np.sum(Y)/len(Y)
St=np.sum([(i-avg_y)**2 for i in Y])

result=[]
for i in range(1,n+1):
    PowerArray=PowerArraySum(PowerArray,X,i*2,Summation_Of_Power)
    RHS=PowerArraySum(RHS,X,i,RHS_Matrix)
    X_Matrix=Form_X_Matrix(Summation_Of_Power,i)
    solution=np.linalg.solve(X_Matrix,RHS_Matrix)
    result.append(solution)


plt.figure(figsize=(10,6))
plt.scatter(X,Y,s=0.1,c='blue')     

color=['red','green','orange','black','cyan','pink','yellow','grey','violet']

x_range=np.arange(min(X),max(X),0.01)
y_range=[]
Sr=[]
r=[]
for i in range(1,n+1):
    ploty=[0]*len(x_range)
    demo_y=[0]*len(X)
    for j in range(i+1):
        ploty+=result[i-1][j]*x_range**j
        demo_y+=result[i-1][j]*np.power(X,j)
    y_range.append(ploty)
    sr=0
    for i in range(len(Y)):
        sr+=(Y[i]-demo_y[i])**2
    Sr.append(sr)
    demo_r=np.sqrt((St-sr)/St)
    r.append(demo_r)


for i in range(1,n+1):
    plt.plot(x_range,y_range[i-1],color=color[i-1],label='Order {}'.format(i))
    print('Order {}:'.format(i))
    for j in range(i+1):
        print('a{}:'.format(j),result[i-1][j])
    print('Sr: ',Sr[i-1],'    St: ',St)
    print('r: ',r[i-1])

plt.legend(loc='upper left')

plt.xlim(min(X)-1,max(X)+1)
plt.ylim(min(Y)-1,max(Y)+1)
plt.xlabel('values of x')
plt.ylabel('values of y')
plt.title('Curve Fitting')

