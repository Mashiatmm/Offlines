import numpy as np
from matplotlib import pyplot as plt
import matplotlib as mp

def reaction(x):   
    if (x==1 or x<=-2):
        print('Invalid input for x=',x)
        return None
    result=x/(1-x)*np.sqrt(2*3.0/(2+x))-.05
    return result


def FalsePos(func,xl,xu,Es,max_i):
    if func(xl)==None or func(xu)==None:
        return None
    if func(xl)*func(xu)>=0:
        print('Define Range otherwise')
        return None
    xr=None
    xro=None
    i=0
    Ea=1.1*Es
    while (Ea>Es and i<max_i):
        fxl=func(xl)
        fxu=func(xu)
        if (fxl==None or fxu==None):
            print('Invalid Value for F(x),fxl:',fxl,'fxu',fxu)
            return None
        xr=xu-((xl-xu)*fxu/(fxl-fxu))
        i+=1
        if (i!=1 and xr!=0):
            Ea=abs((xr-xro)/xr)*100
        fxr=func(xr)
        if(fxr==None):
            print('Invalid Value for f(x),fxr: ',fxr)
            return None
        Test=fxl*fxr
        if(Test==0):
            Ea=0
        elif Test<0:
            xu=xr
            xro=xr
        else:
            xl=xr
            xro=xr
    print('False Position Method: xr=',xr,'\nfunc(xr)=', func(xr),'\nEa=', Ea, '\nNumber of iterations=',i)
    return xr


def SecantMethod(func,sec_guess,xr,Es,max_i):
    if func(sec_guess)==None or func(xr)==None:
        return None
    first_guess=None
    i=0
    Ea=1.1*Es
    while (Ea>Es and i<max_i):
        first_guess=sec_guess
        sec_guess=xr
        f_first=func(first_guess)
        f_sec=func(sec_guess)
        if (f_first==None or f_sec==None):
            print('Invalid Value for F(x)')
            return None
        xr=sec_guess-((first_guess-sec_guess)*f_sec/(f_first-f_sec))
        i+=1
        if (i!=1 and xr!=0):
            Ea=abs((xr-sec_guess)/xr)*100
        fxr=func(xr)
        if(fxr==None):
            print('Invalid Value for f(xr)')
            return None
        if fxr==0:
            Ea=0
    print('Secant Method: xr=',xr,'\nfunc(xr)=', func(xr),'\nEa=', Ea, '\nNumber of iterations=',i)
    return xr

x=np.arange(-1,1,0.1)
y=list(map(reaction,x))

plt.plot(x,y,label='Graphical method')
plt.grid(color='grey',linewidth=0.5)
plt.legend(loc='Upper left')
plt.title('Graphical Representation for the Equation')
plt.xlabel('Values of x')
plt.ylabel('Values for the equation')
plt.show()

Es=0.5
loop=True
max_i=int(input("Max No. of Iterations: "))

print('\n*****False Position Method*****')
while loop:
    xl=float(input("Lower Bound: "))
    xu=float(input("Upper Bound: "))
    xr=FalsePos(reaction,xl,xu,Es,max_i)
    if(xr!=None):
        loop=False

print('\n*****Secant Method*****')
loop=True
while loop:
    first=float(input("Higher Bound: "))
    second=float(input("Lower Bound: "))
    xr=SecantMethod(reaction,first,second,Es,max_i)
    if(xr!=None):
        loop=False

