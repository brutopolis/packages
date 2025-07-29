name io
version 0.1.2
description "buxu io library"
files io.c
setup()
{
    gcc -fPIC -shared -O3 -Wl,-rpath=/lib -o io.brl io.c
}