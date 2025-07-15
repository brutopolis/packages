name bruterlang
version 0.0.9
description "bruterlang dialect for bruter-representation"
files bruterlang.c
setup()
{
    gcc -fPIC -shared -O3 -Wl,-rpath=/lib -o bruterlang.brl bruterlang.c
}