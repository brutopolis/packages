rm -rf minifb
rm -rf lib
git clone https://github.com/emoon/minifb
git clone https://github.com/tsoding/olive.c
mkdir -p lib include
cp olive.c/olive.c include/
cd minifb
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DUSE_OPENGL_API=ON;
make
cd ..
cp build/libminifb.a ../lib/
cp include/*.h ../include/
cd ..
bucc -o bsr.brl bsr.c lib/libminifb.a -Iinclude -lX11 -lm -lGL