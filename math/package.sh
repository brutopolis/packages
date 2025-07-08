name math
version 0.0.9
description "buxu math library"
files math.c
setup()
{
    gcc -fPIC -shared -O3 -Wl,-rpath=/lib -o math.brl math.c -lm
}