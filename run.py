#!/usr/bin/python

import os
import sys
import time

if __name__ == "__main__":
    # To run only specific benchmarks, restrict the [scripts] and [modes] array
    scripts = ['aos', 'soa', 'aosoa']
    modes = ['updates', 'populate']

    total = {}

    os.system('mkdir -p bin')
    for script in scripts:
        os.system('gcc -Wall -O3 -o bin/' + script + ' src/' + script +'.c')
        total[script] = 0

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
