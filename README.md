SimpleLArG4
===========

Based on Dan Pershay's code, I decoupled the particle propogation in materials (GEANT4) and the detector readout simulation.
Currently I am making the input primary particle format more generic.

### Installation

1. Set up the ROOT and GEANT4 environment.
2. Create the build directory, and in the build directory
```shell
cmake -DGeant4_DIR=<path to GEANT4 lib>/lib/Geant4-11.1.0 <path to SimpleLArG4 directory>
make
```

### Run

In the build directory

```shell
./SimpleLArG4 <path to SimpleLArG4 directory>/run.mac
```

### Input files

Convert the MARLEY output files in the ASCII format to the ROOT format for this code.
Note the MARLEY ROOT format and the plain ROOT format MARLEY offers through `marsum` are not compatible.

```shell
root -l
.x MARLEYToROOT.C("/Users/yuntse/data/coherent/preLArTPC/marley/2024/nueArCC_sns_xDir.ascii", "nueArCC_sns_xDir.root")
```

Configure the input and output files in `run.mac`,
> /LArG4/generator/infile <input file path/name> \
> /LArG4/output/outfile <output file path/name>