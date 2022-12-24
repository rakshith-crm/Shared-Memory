import shared
from multiprocessing import Process

shared_list = shared.List('DOG')


def function(integer):
    shared_list.append([integer], [1])

if __name__ == '__main__':
    all_processes = []
    for i in range(100):
        process = Process(target=function, args=(i,))
        all_processes.append(process)

    for i in range(len(all_processes)):
        all_processes[i].start()
    for i in range(len(all_processes)):
        all_processes[i].join()


    values = shared_list.read()
    print(values)