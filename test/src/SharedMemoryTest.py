import shared
import numpy as np
from multiprocessing import Process, shared_memory

shared_list = shared.integerList('CAD')

def function(integer):
    for i in range(10):
        continue
    # shared_list.append([integer], [1])

if __name__ == '__main__':
    all_processes = []
    for i in range(5):
        process = Process(target=function, args=(i,))
        all_processes.append(process)
    
    for i in range(len(all_processes)):
        all_processes[i].start()
    for i in range(len(all_processes)):
        all_processes[i].join()

    # expected = np.arange(N)
    values = shared_list.read()
    values.sort()
    print(values, values.shape)
    # print(expected)
    shared_list.close()