name string
version 0.1.2
description "buxu standard string library"
files string.c
setup()
{
    gcc -fPIC -shared -O3 -Wl,-rpath=/lib -o string.brl string.c
}