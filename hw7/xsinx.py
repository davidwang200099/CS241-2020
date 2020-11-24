import matplotlib.pyplot as plt 
import math
import numpy as np
def xsinx(x):
    return x*math.sin(x)
xx=[]
yy=[]


for i in range(-1,16):
    for j in range(100):
        x=i+j/100.0
        xx.append(x)
        yy.append(xsinx(x))

plt.plot(xx,yy)
plt.show()