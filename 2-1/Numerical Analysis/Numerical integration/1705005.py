import numpy as np
import matplotlib.pyplot as plt

def trapezoid(x1,x2,fx1,fx2):
    I=(x2-x1)*(fx1+fx2)/2
    return I

def simp_one_third(x,fx,start):
    I=(x[start+2]-x[start])/6*(fx[start]+fx[start+2]+4*fx[start+1])
    return I

def simpsons_three_eight(x,fx,start):
    end=start+3;
    I=fx[start]+3*fx[start+1]+3*fx[start+2]+fx[end];
    I=I*3/8*(x[end]-x[start])/3
    return I

f=open('input.txt','r')

if (f.mode=='r'):
    input=f.readlines()
    
n=int(input[0])

x=np.zeros(n)
fx=np.zeros(n)
intervals=np.zeros(n-1)

for i in range(n):
    s=input[i+1].split(' ')
    x[i]=float(s[0])
    fx[i]=float(s[1])
    if(i>0):
        intervals[i-1]=round(x[i]-x[i-1],5)
       
integral=0
p,y,z=0,0,0
p_inter=[]
y_inter=[]
z_inter=[]
distance=intervals[0]
i=1

while i<n-1:
    if(distance!=intervals[i]):
        integral+=trapezoid(x[i-1],x[i],fx[i-1],fx[i])
        p+=1
        p_inter.append(i-1)
    count,start=1,i-1
    while distance==intervals[i]:
        count+=1
        end=i
        i+=1
        if(i>=n-1):
            break
    if(count>1):
        temp=int(count/3)
        one_third_idx=start+temp*3
        
        if(count%3==1):
            temp=temp-1
            one_third_idx=start+temp*3
            y+=2*2
            for j in range(one_third_idx,end+1):
                y_inter.append(j)
            integral+=simp_one_third(x,fx,one_third_idx)
            integral+=simp_one_third(x,fx,one_third_idx+2)
            
        elif(count%3==2):
            y+=2
            y_inter.append(one_third_idx)
            y_inter.append(one_third_idx+1)
            integral+=simp_one_third(x,fx,one_third_idx)
            
        z+=temp*3
        for j in range(start,one_third_idx):
                z_inter.append(j)
        for j in range(temp):
                integral+=simpsons_three_eight(x,fx,start+(j*3))
    
    if(i>=n-1):
            break           
    distance=intervals[i]
    i+=1
    if(i==n-1):
        integral+=trapezoid(x[i-1],x[i],fx[i-1],fx[i])
        p+=1
        p_inter.append(i-1)


print('Trapeziod: {} intervals'.format(p))
print('1/3 rule: {} intervals'.format(y))
print('3/8 rule: {} intervals'.format(z))
print('\nIntegral value: {}'.format(integral))
    
flagp,flagy,flagz=0,0,0     

plt.figure(figsize=(10,6))
plt.grid(color='grey',linestyle='-',alpha=0.2)
for i in p_inter:
    x_list=[x[i],x[i],x[i+1],x[i+1]]
    y_list=[0,fx[i],fx[i+1],0]
    if flagp==0:
        flagp=1
        plt.fill_between(x_list,y_list,color='yellow',label='Trapezoid',alpha=0.5)
    else:
        plt.fill_between(x_list,y_list,color='yellow',alpha=0.5)
        
for i in y_inter:
    x_list=[x[i],x[i],x[i+1],x[i+1]]
    y_list=[0,fx[i],fx[i+1],0]
    if flagy==0:
        flagy=1
        plt.fill_between(x_list,y_list,color='pink',label='1/3rd rule',alpha=0.5)
    else:
        plt.fill_between(x_list,y_list,color='pink',alpha=0.5)

for i in z_inter:
    x_list=[x[i],x[i],x[i+1],x[i+1]]
    y_list=[0,fx[i],fx[i+1],0]
    if flagz==0:
        flagz=1
        plt.fill_between(x_list,y_list,color='palegreen',label='3/8 rule',alpha=0.5)
    else:
        plt.fill_between(x_list,y_list,color='palegreen',alpha=0.5)

plt.plot(x,fx)
plt.scatter(x,fx)
plt.legend(loc='upper left')
plt.xlabel('x values')
plt.ylabel('values of f(x)')
plt.title('Numerical Integration')
plt.show()