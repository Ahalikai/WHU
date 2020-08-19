import random

import numpy as np
import Init
import donminate
from matplotlib.ticker import  MultipleLocator
import matplotlib.pyplot as plt
class NSGA2:
    def __init__(self,nums,dim,iter,x_min,x_max):
        self.pcross=0.4
        self.pmutation=0.1
        self.dim=dim
        self.nums=nums
        self.iters=iter
        self.x_min=x_min
        self.x_max=x_max
        self.new_pop=np.zeros((nums,dim))
        self.pop=[]
        self.crowding_distance=[]


    def crossover(self):
        for i in range(0,self.nums-1,2):

            if(random.random()<self.pcross):
                a=random.random()
                for j in range(self.dim):
                    self.new_pop[i,j]=a*self.pop[i,j]+(1-a)*self.pop[i+1,j]
                    self.new_pop[i+1,j]=a*self.pop[i+1,j]+(1-a)*self.pop[i,j]

    def mutation(self):
        for i in range(self.nums):
            for j in range(self.dim):
                if random.random()<self.pmutation:
                    self.new_pop[i,j]=self.new_pop[i,j]+random.uniform(-1,1)*0.2
                    if(self.new_pop[i,j]<self.x_min):
                        self.new_pop[i,j]=self.x_min
                    if(self.new_pop[i,j]>self.x_max):
                        self.new_pop[i,j]=self.x_max


    def non_donminate(self):
        self.Pareto,self.rank,self.fitness=donminate.non_donminate(self.merge_pop,2*self.nums,self.dim)



    def selection(self):
        self.Pareto,self.rank,self.fitness=donminate.non_donminate(
            self.pop,self.nums,self.dim)

        for i in range(self.nums):
            r1=random.randint(0,self.nums-1)
            r2=random.randint(0,self.nums-1)
            while r1==r2:
                r2 = random.randint(0, self.nums - 1)

            if(self.rank[r1]<self.rank[r2]):
                self.new_pop[i]=self.pop[r1]
            else:
                self.new_pop[i]=self.pop[r2]

    def contact(self):
        self.merge_pop=np.zeros((2*self.nums,self.dim))
        for i in range(self.nums):
            for j in range(self.dim):
                self.merge_pop[i,j]=self.pop[i,j]
                self.merge_pop[i+self.nums,j]=self.new_pop[i,j]

    def init_pop(self):
        self.pop=Init.init_pop(self.nums,self.dim)


    def select_newpop(self):
        self.pop=np.zeros((self.nums,self.dim))
        in1 = np.zeros(self.nums)
        N=0
        count=0
        while N< self.nums:
            N=N+len(self.Pareto[count])
            count=count+1

        k = 0
        if(N==self.nums):

            for i in range(count):
                for j in range(len(self.Pareto[i])):
                    index=self.Pareto[i][j]
                    self.pop[k]=self.merge_pop[index]
                    in1[k]=index
                    k=k+1
        else:
            for i in range(count-1):
                for j in range(len(self.Pareto[i])):
                    index=self.Pareto[i][j]
                    self.pop[k]=self.merge_pop[index]
                    in1[k]=index
                    k=k+1

            add=self.nums-k
            index=count-1
            temp=np.zeros((len(self.Pareto[index]),2))
            for i in range(len(self.Pareto[index])):
                temp[i][0]=self.crowding_distance[self.Pareto[index][i]]
                temp[i][1]=self.Pareto[index][i]
            temp=sorted(temp.tolist())

            for i in range(add):
                a=int(temp[i][1])
                self.pop[k]=self.merge_pop[a]
                in1[k] =a
                k=k+1



    def crowd_distance(self):

        self.crowding_distance=np.zeros((2*self.nums))
        for i in range(len(self.Pareto)-1):
            f1=np.zeros((len(self.Pareto[i]),2))
            f2=np.zeros((len(self.Pareto[i]),2))
            L=len(self.Pareto[i])
            for j in range(L):
                index=self.Pareto[i][j]
                f1[j,0]=self.fitness[index][0]
                f1[j,1]=self.Pareto[i][j]
                f2[j,0]=self.fitness[index][1]
                f2[j,1]=self.Pareto[i][j]
            self.crowding_distance[int(f1[0][1])]=100000
            self.crowding_distance[int(f1[L-1][1])]=100000
            f1_min=f1[0][0]
            f1_max=f1[L-1][0]
            f2_min=f2[0][0]
            f2_max=f2[L-1][0]
            for a in range(1,L-2):

                index=int(f1[a][1])
                self.crowding_distance[index]=\
                    (f1[a+1][0]-f1[a-1][0])/(f1_max-f1_min+1) + (f2[a+1][0]-f2[a-1][0])/(f2_max-f2_min+1)


    def draw(self):

        self.objectives = []  # np.zeros((self.pop,2))
        position = []
        for i in range(self.nums):
            for j in range(self.dim):
                if self.pop[i][j] < 0:
                    self.pop[i][j] = 0
                if self.pop[i][j] > 1:
                    self.pop[i][j] = 1
        self.Pareto, self.rank, self.fitness = donminate.non_donminate(
            self.pop, self.nums, self.dim)

        for i in range(len(self.Pareto[0])):
            position = self.pop[self.Pareto[0][i]]
            f=donminate.Fitness(position,self.dim)
            self.objectives.append(f)
        x = []
        y = []

        for i in range(self.nums):
            x.append(self.fitness[i][0])
            y.append(self.fitness[i][1])
        plt.scatter(x,y)
        plt.show()

        ax = plt.subplot(111)
        plt.scatter(x, y)  # ,marker='+')#self.objectives[:][0],self.objectives[:][1]) #?
        # plt.plot(,'--',label='')       
        plt.axis([0.0, 1.0, 0.0, 1.1])
        xmajorLocator = MultipleLocator(0.1)
        ymajorLocator = MultipleLocator(0.1)
        ax.xaxis.set_major_locator(xmajorLocator)
        ax.yaxis.set_major_locator(ymajorLocator)
        plt.xlabel('f1')

        plt.ylabel('f2')
        plt.title('ZDT2 Pareto Front')
        plt.grid()
        plt.show()

    def run(self):
        self.init_pop()

        self.selection()
        self.crossover()
        self.mutation()

        for i in range(self.iters):
            print(i)
            self.crossover()
            self.mutation()
            self.contact()
            self.non_donminate()
            self.crowd_distance()
            self.select_newpop()
        self.draw()



