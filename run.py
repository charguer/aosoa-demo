#!/usr/bin/python

import os
import sys
import time

if __name__ == "__main__":
    # To run only specific benchmarks, restrict the [scripts] and [modes] array
    scripts = ['aos', 'soa', 'aosoa']
    modes = ['updates', 'populate']

    #scripts = ['aosoa'] 
    # modes = ['updates']

    total = {}

    os.system('rm -f bin/*')
    os.system('mkdir -p bin')
    for script in scripts:  
        options = ''
        # options = '-fopt-info-vec-all 2> bin/' + script + '_infos.txt'
        command = 'gcc -std=c11 -march=native -Wall -O3 -o bin/' + script + ' src/' + script + '.c ' + options
        print(command)
        os.system(command)
        total[script] = 0

    # quit()

    for mode in modes:
        for script in scripts:
            start = time.time()
            os.system('./bin/' + script + ' ' + mode)
            end = time.time()
            t = end - start
            total[script] += t
            print(mode + ' using ' + script + ': %.02f' % t)
        print('')

    for script in scripts:
        print('total using ' + script + ': %.02f' % total[script])
