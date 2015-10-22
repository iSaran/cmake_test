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

After you install it change to BHand download directory and export the path. If
you downloaded BHand in your home directory:

```bash
cd ~/Bhand/API
echo "export BHAND_INCLUDE_DIR=$PWD" >> ~/.bashrc
source ~/.bashrc
```

## Build

In order to build it change inside `cmake_test` directory:

```bash
mkdir build
cd build
cmake ..
make
```
