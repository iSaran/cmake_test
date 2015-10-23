# cmake_test

## Depedencies

### CMake

```bash
sudo apt-get install cmake
```

### BHand C++ software installation

Follow the instructions from
[here](http://support.barrett.com/wiki/Hand/282/SoftwareSetup/Linux) in order
to install BHand.

## Build

In order to build it change inside `cmake_test` directory:

```bash
mkdir build
cd build
cmake ..
make
```

If you encounter an issue with BHand library, you should edit `CMakeLists.txt`
and insert the path that you downloaded BHand C++ Software.
