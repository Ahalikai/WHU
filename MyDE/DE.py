import random
import math
import numpy as np
def fitness( x):
    s1 = 0.
    s2 = 1.
    for i in range(1, 2 + 1):
        s1 = s1 + x[i - 1] ** 2
        s2 = s2 * math.cos(x[i - 1] / math.sqrt(i))
    y = (1. / 4000.) * s1 - s2 + 1
    y = 1. / (1. + y)
    return y

def fitness(x):
    return -x*(x-4)
class DE():
    def __init__(self,dim,size,iter,min_x,max_x):
        self.dim=dim
        self.num=size
        self.iters=iter
        self.min_x=min_x
        self.max_x=max_x
        self.F=0.5
        self.CR=0.7

    def init_pop(self):
        self.pop=np.zeros((self.num,self.dim))
        for i in range(self.num):
            for j in range(self.dim):

                self.pop[i, j] =self.min_x+random.random()*(self.max_x-self.min_x)

        self.evaluate()
        self.best=np.max(self.fitness)
       # self.best_x=self.pop
       # self.best_fit=self.fitness

    def evaluate(self):
        fit = []
        for i in range(self.num):
            fit.append(fitness(self.pop[i]))
        self.fitness = np.array(fit)

    def mutation(self):
        self.mu=np.zeros((self.num,self.dim))
        for i in range(self.num):
            r1=r2=r3=0
            while (r1==i or r2==i or r3==i or r1==r2 or r2==r3 or r1==r3):
                r1 = random.randint(0, self.num - 1)  # 随机数范围为[0,size-1]的整数
                r2 = random.randint(0, self.num - 1)
                r3 = random.randint(0, self.num - 1)
            self.mu[i]=self.pop[r1]+self.F*(self.pop[r2]-self.pop[r3])
            for j in range(self.dim):
                if(self.mu[i,j]<self.min_x):
                    self.mu[i,j]=self.min_x
                if(self.mu[i,j]>self.max_x):
                    self.mu[i,j]=self.max_x

    def crossover(self):
        self.cross = np.zeros((self.num, self.dim))
        for i in range(self.num):
            for j in range(self.dim):
                random_j=random.randint(0,self.dim-1)
                r=random.random()
                if(r<self.CR or random_j==j):
                    self.cross[i,j]=self.mu[i,j]
                else:
                    self.cross[i,j]=self.pop[i,j]

    def selection(self):
        for i in range(self.num):
            if(fitness(self.pop[i]) > fitness(self.cross[i])):
                self.pop[i]=self.pop[i]
            else:
                self.pop[i]=self.cross[i]

    def update(self):
        self.mutation()
        self.crossover()
        self.selection()
        self.evaluate()

        temp=np.max(self.fitness)
        if(temp>self.best):
            self.best=temp
        print(self.best)
        #self.fitness_val_list.append(self)

    def run(self):
        self.init_pop()
        for i in range(self.iters):
            print(i)
            self.update()



if __name__ =='__main__':
    de=DE(1,10,50,-100,100)
    de.run()