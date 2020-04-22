#!/usr/bin/python

import os
import sys
import subprocess

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
        options = '-fopt-info-vec-all 2> bin/' + script + '_infos.txt'
        command = 'gcc-9.1 -std=c11 -march=native -Wall -O3 -o bin/' + script + ' src/' + script + '.c ' + options
        print(command)
        os.system(command)
        total[script] = 0

    # quit()

    for mode in modes:
        for script in scripts:
            program = './bin/' + script
            result = subprocess.Popen([program, mode], stdout=subprocess.PIPE).communicate()[0]
            exectime = float(result)
            print(mode + ' using ' + script + ': %.02f' % exectime)
            total[script] += exectime
        print('')

    for script in scripts:
        print('total using ' + script + ': %.02f' % total[script])
