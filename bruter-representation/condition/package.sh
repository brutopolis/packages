name condition
version 0.1.2
description "buxu conditions library"
files condition.c
setup()
{
    gcc -fPIC -shared -O3 -Wl,-rpath=/lib -o condition.brl condition.c -lm
}