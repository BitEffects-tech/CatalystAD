# CatalystAD

Cross-platform parametric CAD software focusing on a user-friendly interface.

## Setup

First, clone the project and the submodules
```
git clone https://github.com/BitEffects-tech/CatalystAD

git submodule update --init --recursive
```

Next create the build folder and prepare the makefile
```
mkdir build
cd build
cmake ..
```

To build and run the test cases
```
make -j16 && ./runUnitTests
```

To build and run the app
```
make -j16 && ./CatalystAD
```
