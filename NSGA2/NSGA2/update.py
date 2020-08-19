import numpy as np
import random
def crossover(pop,num,dim):
    new_pop=np.zeros((num,dim))
    for i in range(0, num - 1, 2):
        print(i)
        if (random.random() < .pcross):
            a = random.random()
            for j in range(self.dim):
                self.new_pop[i, j] = a * self.pop[i, j] + (1 - a) * self.pop[i + 1, j]
                self.new_pop[i + 1, j] = a * self.pop[i + 1, j] + (1 - a) * self.new_pop[i, j]