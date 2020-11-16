# First remove old directories
rm -rf bin
rm -rf build
rm -rf lib

# Now re-create these
mkdir -p bin
mkdir -p build
mkdir -p lib

# Enter into the build directory and run CMake
cd build
cmake ..
make

# Now copy all lib files
cd ..
cp -r build/bin bin
cp -r build/lib lib