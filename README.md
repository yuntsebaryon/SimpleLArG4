SimpleLArG4
===========

Based on Dan Pershay's code, I decoupled the particle propogation in materials (GEANT4) and the detector readout simulation.

The current detector geometry is described as
  - Center: (0, 0, 0)cm
  - Vacuum: a sphere with the radius of 30m
  - LAr: a cube with (400cm)<sup>3</sup> with the center above

Currently only the ROOT file format produced with `macros/MARLEYToROOT.C` is supported as the input file format, through the `MARLEYGenerator` class.  I am planning to make the input more generic (to include cosmic ray background as the first step).

The neutrino interaction vertex is now hardcoded at (x, y, z) = (0, 0, 0), and the plan is to make it configurable.

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