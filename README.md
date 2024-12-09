# Authors 
**Elena Ruiz de la Cuesta**: elenaruizdelacuestacastano@gmail.com

**Giovanni Lucarelli**: 
giovanni.lucarelli@studenti.units.it

# sci-toolbox
This is the project for the second homework assignment of the course Advanced Programming @ University of Trieste. It implements a scientific toolbox consisting of two modules:
- Statistics module (A);
- Interpolation module (B).

## Table of contents

1. [Project structure](#project-structure)
2. [How to build](#how-to-build)
3. [Module A: Statistics](#module-a-statistics-module)
4. [Module B: Interpolation](#module-d-ode-module)
5. [Workload division and references](#workload-division-and-external-references)

## Project structure

```
📂 project/
│ 
├── 📂 apps/
│   └── 📄 stats_app.cpp
│ 
├── 📂 datasets/
│   └── 📊 iris.csv
│
├── 📂 include/	
│   └── 📄 dataframe.hpp
│ 
├── 📂 output/
│
├── 📂 src/
│   ├── 📝 CMakeLists.txt
│   └── 📄 dataframe.cpp
│
├── 📒 .gitignore
├── 📝 CMakeLists.txt
└── 📰 README.md
```
## How to build

The Statistics module implements functions from *GSL-GNU Scientific Library*, so its necessary to install it before building the toolbox.

The build process is based on CMake and the CMake files are providede. From the root folder of the project:

Create a folder `build/` and move inside it:
```bash
mkdir build && cd build
```

Run
```bash
cmake ..
```
and then compile the program with
```bash
make
```

**How to use the two modules separately?**

## Module A: Statistics

### DataFrame class
- choice motivation
- general structure 
- row iterator

### How to run stats_app.cpp
