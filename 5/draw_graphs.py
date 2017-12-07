#!/usr/local/bin/python3
import matplotlib.pyplot as plt
import numpy as np

bases = ["rk", "ta"]
nums = ["1", "2"]
types = ["_pos", "_vel"]

for base in bases:
    for num in nums:
        plots = []
        for type in types:
            name = base + num + type
            with open(name + ".txt") as f:
                lines = [float(x.rstrip()) for x in f.readlines()]
                T = lines[0]
                tmax = lines[1]
                y = np.array(lines[2:])
                x = np.arange(0, tmax+T, T)
                plot_, = plt.plot(x, y, label=name)
                plots.append(plot_)
        plt.legend(handles=[plots[0], plots[1]])
        plt.show()

