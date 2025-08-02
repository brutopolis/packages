name condition
files condition.c
version 0.0.1
description "feraw standard conditions library"
setup()
{
    gcc -fPIC -shared -O3 -Wl,-rpath=/lib -o condition.brl condition.c
}