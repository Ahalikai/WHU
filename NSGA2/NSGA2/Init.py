import  numpy as np
import random
def init_pop(nums,dim):
    pop=np.zeros((nums,dim))
    for i in range(nums):
        for j in range(dim):
            pop[i,j]=random.random()

    return pop
