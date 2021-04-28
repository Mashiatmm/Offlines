import numpy as np


def forward_elimination(C,n):
    A=C.copy()
    L=np.identity(n)
    for i in range(n):
        for j in range(i):
            factor=A[i][j]/A[j][j]
            L[i][j]=factor
            A[i]=A[i]-A[j]*factor
    return A,L
            
def unique_solution(U,n):
    for i in range(n):
        if(not np.any(U[i])):
            return False
    return True

def lower_backward_substitution(L,B,n):
    Y=np.zeros(n)
    for i in range(n):
        Y[i]=B[i]
        for j in range(i):
            Y[i]-=L[i][j]*Y[j]
        Y[i]/=L[i][i]
    return Y
    
def upper_backward_substitution(U,Y,n):
    X=np.zeros(n)
    for i in range(n-1,-1,-1):
        X[i]=Y[i]
        for j in range(i+1,n):
            X[i]-=U[i][j]*X[j]
        X[i]/=U[i][i]
    return X
    

f=open("in1.txt","r")
contents=[]
if f.mode=='r':
    s=f.readline()
    while(s!=''):
        contents.append(s)
        s=f.readline()
f.close()
#print(contents)    
n=int(contents[0])

A=np.zeros((n,n))
    
for i in range(n):
        num=contents[i+1].split(' ')
        for j in range(n):
            A[i][j]=float(num[j])
       
B=np.zeros(n)
for i in range(n):
    B[i]=float(contents[i+n+1])

U,L=forward_elimination(A,n)
unique=unique_solution(U,n)

np.set_printoptions(formatter={'float': '{: 0.4f}'.format})
out=open("out1.txt","w")
print(L)
s=""
for i in range(n):
    for j in range(n):
        s+=str("%0.4f"%L[i][j])
        s+=" "
    s+='\n'
s+="\n"
out.write(s)
    
    
print(U)
s=""
for i in range(n):
    for j in range(n):
        s+=str("%0.4f"%U[i][j])
        s+=" "
    s+='\n'
s+="\n"
out.write(s)
 
if(not unique):
    out.write("No unique solution")
else:
    Y=lower_backward_substitution(L,B,n)
    X=upper_backward_substitution(U,Y,n)
    print(Y)
    s=""
    for i in range(n):
       s+=str("%0.4f"%Y[i])
       s+="\n"
    s+="\n"
    out.write(s)
    
    print(X)
    s=""
    for i in range(n):
        s+=str("%0.4f"%X[i])
        s+="\n"
    s+="\n"
    out.write(s)

out.close()
            
