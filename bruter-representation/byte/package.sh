name byte
version 0.1.0
description "buxu byte library"
files byte.c
setup()
{
    gcc -fPIC -shared -O3 -Wl,-rpath=/lib -o byte.brl byte.c -lm
}