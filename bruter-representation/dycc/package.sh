name dycc
version 0.1.8
description "buxu foreign function interface"
files dycc.c
setup()
{
    gcc -fPIC -shared -O3 -Wl,-rpath=/lib -o dycc.brl dycc.c -ltcc
}