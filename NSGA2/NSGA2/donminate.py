import numpy as np


def  Fitness(x,dim):
    f1=x[0]
    f=0
    for i in range(dim-1):
        f=f+9*(x[i+1])/(dim-1)
    g=1+f
    f2=g*(1-np.square(f1/g))
    return f1,f2

def donminate( x,y):
    equal=1
    for i in range(len(x)):
        if(x[i]!=y[i]):
            equal=0
    if(equal==1):
        return False

    for  i in range(len(x)):
        if(x[i]>y[i]):
            return False
    return  True



def non_donminate(pop,num,dim):
    P=[]
    P.append([])
    Np=np.zeros(num)
    rank=np.zeros(num)
    Sp=[]
    fit=[]
    for i  in range(num):
        f=Fitness(pop[i],dim)
        fit.append(f)
    fitness=np.array(fit)

    for i in range(num):
        temp=[]
        for j in range(num):
            if (i == j):
                continue
            if(donminate(fitness[i],fitness[j])):  #i支配j
                temp.append(j)

            if(donminate(fitness[j],fitness[i])): #j支配i
                Np[i]=Np[i]+1

        Sp.append(temp)
        if(Np[i]==0):
            P[0].append(i)
            rank[i]=1

    i=0
    while(len(P[i])>0):
        H=[]
        for j in range(len(P[i])):
            index=P[i][j]
            for k in range(len(Sp[index])):
                index2=Sp[index][k]
                Np[index2]=Np[index2]-1

                if(Np[index2]==0):
                    H.append(Sp[index][k])
                    rank[index2]=i+2

        i=i+1
        P.append(H)


    return P,rank,fitness





#a1=np.array([[0,3],[0,3],[1,2],[2,1],[3,0],[2,2],[3,3],[0.3,2.5],[6,6],[7,5]])
#non_donminate(a1,10,2)