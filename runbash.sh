rm -rf build
mkdir build
cd build
cmake ..
make -j 64
cd ../bin
./runtest