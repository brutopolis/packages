name bit
version 0.0.7
description "buxu bit library"
files bit.c
setup()
{
    gcc -fPIC -shared -O3 -Wl,-rpath=/lib -o bit.brl bit.c -lm
}