git clone https://github.com/emoon/minifb.git;
cd minifb;
mkdir build;
cd build;
cmake .. -DUSE_WAYLAND_API=OFF -DUSE_OPENGL_API=ON;
make;
sudo make install;
cd ..;
cd ..;
