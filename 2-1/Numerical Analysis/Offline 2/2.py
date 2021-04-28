import numpy as np

def find_min_intercept(tableu,idx):
    Intercept=[]
    for i in range(1,row):
        if(tableu[i][idx]==0 or tableu[i][column-1]/tableu[i][idx]<0):
            Intercept.append(float("inf"))
        else:
            Intercept.append(tableu[i][column-1]/tableu[i][idx])
    pivot_val,pivot_idx=min((val, idx) for (idx, val) in enumerate(Intercept))
    pivot_idx+=1
    return pivot_val,pivot_idx
    

def row_operations(tableu,idx_col,pivot_idx_row,pivot_val):
    tableu[pivot_idx_row]/=tableu[pivot_idx_row][idx_col]
    for i in range(row):
        if(i==pivot_idx_row):
            continue
        tableu[i]=tableu[i]-(tableu[pivot_idx_row]*tableu[i][idx_col]/tableu[pivot_idx_row][idx_col])



input=open("in2.txt","r")

if(input.mode=="r"):
    line=[]
    s=input.readline()
    while(s!=''):
        line.append(s)
        s=input.readline()
input.close()

row=len(line)   
first_line=line[0].split(' ')
column=row+len(first_line)+1
print(row,column)   

tableu=np.zeros((row,column))
#make objective row
tableu[0][0]=1
mat=line[0].split(' ')
for j in range(len(mat)):
    tableu[0][j+1]=-float(mat[j])

count=len(first_line)
for i in range(1,len(line)):
    mat=line[i].split(' ')
    count+=1
    tableu[i][count]=1
    for j in range(len(mat)-1):
        tableu[i][j+1]=float(mat[j])
    tableu[i][column-1]=float(mat[len(mat)-1])
   
np.set_printoptions(formatter={'float': '{: 0.2f}'.format})
print("Tableu:")
print(tableu)


flag=True
while (True):
    if np.all(tableu[0]>=0):
        break
    
    val, idx = min((val, idx) for (idx, val) in enumerate(tableu[0]))
    #Intercept=[tableu[i][column-1]/tableu[i][idx] for i in range(1,row)]
    pivot_val,pivot_idx_row=find_min_intercept(tableu,idx)
    row_operations(tableu,idx,pivot_idx_row,pivot_val)
    print()
    print(tableu)

#Output
result=tableu[0][column-1]
var_num=len(line[0].split(' '))
variables=[]
for i in range(var_num):
    if(tableu[0][i+1]>0):
        temp=0
        variables.append(temp)
        #variables.append(0)
    else:
        for j in range(1,row):
            if(tableu[j][i+1])==1:
                variables.append("%0.2f"%tableu[j][column-1])
                break

print("\nMaximum value: ""%0.2f"%result)
print("variables: ",variables)
    

