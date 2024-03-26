#!/usr/bin/env python
import os

if __name__ == "__main__":

    inDir = '/Users/yuntse/data/coherent/preLArTPC/marley/2024'
    outDir = inDir

    nFiles = 10

    for iFile in range( nFiles ):

        infile = f'{inDir}/nueArCC_sns_yDir_{iFile:02d}.ascii'
        outfile = f'{outDir}/nueArCC_sns_yDir_{iFile:02d}.root'

        cmd = f'root -q -b \'MARLEYToROOT.C(\"{infile}\", \"{outfile}\")\''
        print( cmd )
        os.system( cmd )